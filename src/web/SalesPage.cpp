//
//  SalesPage.cpp
//
//  Created by Julian Koksal on 2022-11-13.
//

#include "SalesPage.hpp"

const int SalesPage::NUM_DAYS_TO_CHART = 366;

const std::vector<Wt::WColor> SalesPage::COLOUR_PALETTE = {
    Wt::WColor(230, 0, 230),  // ANSI bright magenta
    Wt::WColor(0, 230, 230),  // ANSI bright cyan
    Wt::WColor(230, 0, 0),    // ANSI bright red
    Wt::WColor(0, 217, 0),    // ANSI bright green
    Wt::WColor(230, 230, 0),  // ANSI bright yellow
    Wt::WColor(0, 0, 255),    // ANSI bright blue
    Wt::WColor(255, 128, 0),  // orange
    Wt::WColor(128, 0, 255),  // purple
    Wt::WColor(0, 128, 255),  // light blue
    Wt::WColor(0, 100, 0)     // dark green
};

SalesPage::SalesPage()
{
    bool isLoggedIn = ((Application *)Application::instance())->getAuth()->IsLoggedIn();
    if (!isLoggedIn)
    {
        return;
    }
    
    // Loads HTML template and CSS styles.
    addStyleClass("list");
    addStyleClass("list-wide");
    Wt::WTemplate *salesTemplate = addNew<Wt::WTemplate>(tr("sales-chart"));
    
    // Inital selected value
    menuItemsToChart = { "All menu items" };
    
    // The menu is read from the database only once to prevent errors if the menu is changed by some other session.
    menu = DBHelper::getInstance().selectWhere(MenuItem(), {}, "name");
    
    // The chart model.
    std::shared_ptr<Wt::WStandardItemModel> model = std::make_shared<Wt::WStandardItemModel>(NUM_DAYS_TO_CHART, 1 + 2 * (menu.size() + 1));
    
    // Chart and legend.
    Wt::Chart::WCartesianChart *chart = salesTemplate->bindWidget("chart", createChartWidget(model));
    Wt::WContainerWidget *legend = salesTemplate->bindWidget("legend", createLegendWidget());
    
    // Y-axis
    Wt::WText *yAxisTitle = salesTemplate->bindWidget("y-axis-title", std::make_unique<Wt::WText>("Total Revenue ($)"));
    yAxisTitle->addStyleClass("y-axis-title");
    
    // Rev($)-Qty(#) button group
    Wt::WContainerWidget *btnGroupRevQty = salesTemplate->bindWidget("btn-group-rev-qty", createBtnGroupRevQty(chart, salesTemplate, yAxisTitle));
    
    // Dialog opened by the "Select menu items..." button.
    Wt::WDialog *dialog = addChild(createDialogWidget(chart, salesTemplate));
    
    // "Select menu items..." button.
    Wt::WPushButton *btnOpenDialog = salesTemplate->bindWidget("btn-menu-item", createBtnOpenDialogWidget());
    btnOpenDialog->clicked().connect([dialog, btnOpenDialog] {
        onBtnOpenDialogClick(dialog, btnOpenDialog);
    });
    
    updateModel(model.get());
    showSeries(chart, salesTemplate);
}

SalesPage::~SalesPage()
{
    
}

std::unique_ptr<Wt::Chart::WCartesianChart> SalesPage::createChartWidget(std::shared_ptr<Wt::WStandardItemModel> model)
{
    // Fonts
    Wt::WFont fontBold = Wt::WFont();
    fontBold.setFamily(Wt::FontFamily::Monospace, "'SF Mono Bold'");
    Wt::WFont fontRegular = Wt::WFont();
    fontRegular.setFamily(Wt::FontFamily::Monospace, "'SF Mono Regular'");
    Wt::WFont fontSmall = fontRegular;
    fontSmall.setSize(Wt::FontSize::Small);

    // Colours
    Wt::WColor colourDarkGray = Wt::WColor(29, 28, 29);
    Wt::WColor colourLightGray = Wt::WColor(51, 51, 51);
    Wt::WColor colourWhite = Wt::WColor(255, 255, 255);
    
    
    // Chart
    std::unique_ptr<Wt::Chart::WCartesianChart> chart = std::make_unique<Wt::Chart::WCartesianChart>();
    chart->setType(Wt::Chart::ChartType::Scatter);
    chart->setModel(model);
    
    // Styling
    chart->setTextPen(Wt::WPen(colourWhite));
    chart->setBackground(colourDarkGray);
    chart->setPlotAreaPadding(70, Wt::Side::Left);
    chart->setPlotAreaPadding(35, Wt::Side::Right);
    chart->resize("42em", "30em");
    chart->setPanEnabled();
    
    // X-axis
    chart->setXSeriesColumn(0);
    Wt::Chart::WAxis &xAxis = chart->axis(Wt::Chart::Axis::X);
    xAxis.setScale(Wt::Chart::AxisScale::Date);
    xAxis.setLabelFormat("yyyy-MM-dd");
    xAxis.setLabelFont(fontSmall);
    xAxis.setLabelInterval(7);
    xAxis.setRange(Wt::WDate::currentDate().toJulianDay() - NUM_DAYS_TO_CHART, Wt::WDate::currentDate().toJulianDay() - 1);
    xAxis.setZoomRange(Wt::WDate::currentDate().toJulianDay() - 20, Wt::WDate::currentDate().toJulianDay() - 1);
    xAxis.setMaximumZoomRange(20);
    
    // Y-axis
    Wt::Chart::WAxis &yAxis = chart->axis(Wt::Chart::Axis::Y);
    yAxis.setLabelFont(fontSmall);
    yAxis.setLabelFormat("%.0f");
    yAxis.setGridLinesEnabled(true);
    yAxis.setGridLinesPen(Wt::WPen(colourLightGray));
    
    // Series
    
    // "All menu items" series colours.
    Wt::WColor seriesAllColour = COLOUR_PALETTE[0];
    Wt::WPen seriesAllPen = Wt::WPen(seriesAllColour);
    seriesAllPen.setWidth(2);
    Wt::WBrush seriesAllBrush = Wt::WBrush(seriesAllColour);
    
    // "All menu items" revenue series.
    std::unique_ptr<Wt::Chart::WDataSeries> seriesRevenueAll = std::make_unique<Wt::Chart::WDataSeries>(1, Wt::Chart::SeriesType::Line);
    seriesRevenueAll->setMarker(Wt::Chart::MarkerType::Circle);
    seriesRevenueAll->setPen(seriesAllPen);
    seriesRevenueAll->setMarkerBrush(seriesAllBrush);
    chart->addSeries(std::move(seriesRevenueAll));
    
    // "All menu items" quantity series.
    std::unique_ptr<Wt::Chart::WDataSeries> seriesQuantityAll = std::make_unique<Wt::Chart::WDataSeries>(2 + (int)menu.size(), Wt::Chart::SeriesType::Line);
    seriesQuantityAll->setMarker(Wt::Chart::MarkerType::Circle);
    seriesQuantityAll->setPen(seriesAllPen);
    seriesQuantityAll->setMarkerBrush(seriesAllBrush);
    chart->addSeries(std::move(seriesQuantityAll));
    
    // Iterates the menu and creates a revenue series and a quantity series for each menu item.
    int col = 2;
    for (std::vector<MenuItem>::iterator it = menu.begin(); it != menu.end(); ++it)
    {
        // Series colours.
        Wt::WColor seriesColour = COLOUR_PALETTE[(col - 1) % COLOUR_PALETTE.size()];
        Wt::WPen seriesPen = Wt::WPen(seriesColour);
        seriesPen.setWidth(2);
        Wt::WBrush seriesBrush = Wt::WBrush(seriesColour);
        
        // Revenue series.
        std::unique_ptr<Wt::Chart::WDataSeries> seriesRevenue = std::make_unique<Wt::Chart::WDataSeries>(col, Wt::Chart::SeriesType::Line);
        seriesRevenue->setMarker(Wt::Chart::MarkerType::Circle);
        seriesRevenue->setPen(seriesPen);
        seriesRevenue->setMarkerBrush(seriesBrush);
        chart->addSeries(std::move(seriesRevenue));
        
        // Quantity series.
        std::unique_ptr<Wt::Chart::WDataSeries> seriesQuantity = std::make_unique<Wt::Chart::WDataSeries>(col + (int)menu.size() + 1,
                                                                                                          Wt::Chart::SeriesType::Line);
        seriesQuantity->setMarker(Wt::Chart::MarkerType::Circle);
        seriesQuantity->setPen(seriesPen);
        seriesQuantity->setMarkerBrush(seriesBrush);
        chart->addSeries(std::move(seriesQuantity));
        
        col++;
    }
    
    return chart;
}

std::unique_ptr<Wt::WContainerWidget> SalesPage::createLegendWidget()
{
    std::unique_ptr<Wt::WContainerWidget> legend = std::make_unique<Wt::WContainerWidget>();
    
    // If no series are selected then no legend is shown.
    if (menuItemsToChart.empty())
    {
        return legend;
    }
    
    legend->addStyleClass("chart-legend");
    
    if (menuItemsToChart.count("All menu items"))
    {
        legend->addWidget(createLegendItemWidget("All menu items", COLOUR_PALETTE[0]));
    }
    
    int i = 1;
    for (std::vector<MenuItem>::iterator it = menu.begin(); it != menu.end(); ++it)
    {
        if (menuItemsToChart.count(it->getName()))
        {
            legend->addWidget(createLegendItemWidget(it->getName(), COLOUR_PALETTE[i % COLOUR_PALETTE.size()]));
        }
        i++;
    }
    
    return legend;
}

std::unique_ptr<Wt::WContainerWidget> SalesPage::createLegendItemWidget(std::string menuItemName, Wt::WColor colour)
{
    std::unique_ptr<Wt::WContainerWidget> legendItem = std::make_unique<Wt::WContainerWidget>();
    legendItem->addStyleClass("flex-row");
    
    Wt::WCssDecorationStyle txtStyle = Wt::WCssDecorationStyle();
    txtStyle.setForegroundColor(colour);
    
    Wt::WText *lineTxt = legendItem->addNew<Wt::WText>("-&nbsp;");
    lineTxt->setDecorationStyle(txtStyle);
    
    legendItem->addNew<Wt::WText>(menuItemName);
    
    return legendItem;
}

std::unique_ptr<Wt::WDialog> SalesPage::createDialogWidget(Wt::Chart::WCartesianChart *chart, Wt::WTemplate *salesTemplate)
{
    std::unique_ptr<Wt::WDialog> dialog = std::make_unique<Wt::WDialog>();
    dialog->setTitleBarEnabled(false);
    dialog->setModal(false);
    dialog->setMovable(false);
    
    Wt::WContainerWidget *dialogContents = dialog->contents();
    dialogContents->addStyleClass("sales-dialog");
    
    dialogContents->addWidget(createDialogItemWidget(chart, salesTemplate, "All menu items"));
    for (std::vector<MenuItem>::iterator it = menu.begin(); it != menu.end(); ++it)
    {
        dialogContents->addWidget(createDialogItemWidget(chart, salesTemplate, it->getName()));
    }
    
    return dialog;
}

std::unique_ptr<Wt::WContainerWidget> SalesPage::createDialogItemWidget(Wt::Chart::WCartesianChart *chart, Wt::WTemplate *salesTemplate, std::string menuItemName)
{
    std::unique_ptr<Wt::WContainerWidget> item = std::make_unique<Wt::WContainerWidget>();
    
    Wt::WCheckBox *checkbox = item->addNew<Wt::WCheckBox>();
    checkbox->checked().connect([this, chart, salesTemplate, menuItemName] {
        menuItemsToChart.insert(menuItemName);
        showSeries(chart, salesTemplate);
    });
    checkbox->unChecked().connect([this, chart, salesTemplate, menuItemName] {
        menuItemsToChart.erase(menuItemName);
        showSeries(chart, salesTemplate);
    });
    
    if (menuItemsToChart.count(menuItemName))
    {
        checkbox->setChecked();
    }
    
    item->addNew<Wt::WText>("<label for='" + checkbox->id() + "'>" + menuItemName + "</label>");
    
    return item;
}

std::unique_ptr<Wt::WContainerWidget> SalesPage::createBtnGroupRevQty(Wt::Chart::WCartesianChart *chart, Wt::WTemplate *salesTemplate, Wt::WText *yAxisTitle)
{
    std::unique_ptr<Wt::WContainerWidget> container = std::make_unique<Wt::WContainerWidget>();
    container->addStyleClass("sales-btn-group-rev-qty");
    
    std::shared_ptr<Wt::WButtonGroup> group = std::make_shared<Wt::WButtonGroup>();
    Wt::WButtonGroup *groupRawPtr = group.get();
    groupRawPtr->checkedChanged().connect([this, groupRawPtr, chart, salesTemplate, yAxisTitle](Wt::WRadioButton *selection) {
        selectedIDRevQty = groupRawPtr->id(selection);
        showSeries(chart, salesTemplate);
        setYAxisTitle(yAxisTitle);
    });
    
    Wt::WRadioButton *btn;
    
    btn = container->addNew<Wt::WRadioButton>("Rev($)");
    group->addButton(btn, 0);
    
    btn = container->addNew<Wt::WRadioButton>("Qty(#)");
    group->addButton(btn, 1);
    
    group->setSelectedButtonIndex(0);
    
    return container;
}

std::unique_ptr<Wt::WPushButton> SalesPage::createBtnOpenDialogWidget()
{
    std::unique_ptr<Wt::WPushButton> btn = std::make_unique<Wt::WPushButton>("Select menu items...");
    btn->addStyleClass("sales-select-menu-btn");
    
    return btn;
}

void SalesPage::onBtnOpenDialogClick(Wt::WDialog *dialog, Wt::WPushButton *btnOpenDialog)
{
    if (dialog->isVisible())
    {
        dialog->hide();
    }
    else
    {
        dialog->show();
        dialog->positionAt(btnOpenDialog);
    }
}

void SalesPage::updateModel(Wt::WAbstractItemModel *model)
{
    // Iterates from yesterday to numDaysToChart days ago.
    for (int daysAgo = 1; daysAgo <= NUM_DAYS_TO_CHART; daysAgo++)
    {
        Wt::WDate day = Wt::WDate::currentDate().addDays(daysAgo * -1);
        std::string dayStr = day.toString("yyyy-MM-dd").toUTF8() + " 00:00:00";
        int daySeq = NUM_DAYS_TO_CHART - daysAgo;
        
        model->setData(daySeq, 0, day); // Sets the first column (x-axis).
        
        std::vector<vOrderSales> sales = DBHelper::getInstance().selectWhere(vOrderSales(), { SqlCondition("salesDate", "=", dayStr), },
                                                                             "isAllMenuItems DESC, menuItemName");
        
        int col = 1;
        // If sales is empty, set all values for the day to 0.
        if (sales.empty())
        {
            for (col = 1; col < menu.size() + 2; ++col)
            {
                model->setData(daySeq, col, 0.0);
                model->setData(daySeq, col + (int)menu.size() + 1, 0);
            }
        }
        for (std::vector<vOrderSales>::iterator it = sales.begin(); it != sales.end(); ++it)
        {
            std::string menuItemName = it->getMenuItemName();
            
            // If a menu item had 0 sales for the day it will not be in the sales vector.
            // Set the column for that menu item to 0 and move on to the next column.
            if (col != 1)
            {
                while (menuItemName != menu[col - 2].getName())
                {
                    model->setData(daySeq, col, 0.0);
                    model->setData(daySeq, col + (int)menu.size() + 1, 0);
                    ++col;
                }
            }
            
            double totalRevenue = it->getTotalRevenue();
            int totalQuantity = it->getTotalQuantity();
            
            model->setData(daySeq, col, totalRevenue);
            model->setData(daySeq, col + (int)menu.size() + 1, totalQuantity);
            
            double &maxRevenue = maxSeriesRevenue[menuItemName];
            if (totalRevenue > maxRevenue)
            {
                maxRevenue = totalRevenue;
            }
            
            int &maxQuantity = maxSeriesQuantity[menuItemName];
            if (totalQuantity > maxQuantity)
            {
                maxQuantity = totalQuantity;
            }
            
            ++col;
        }
    }
}

void SalesPage::showSeries(Wt::Chart::WCartesianChart *chart, Wt::WTemplate *salesTemplate)
{
    if (selectedIDRevQty == 0)
    {
        chart->series(1).setHidden(!menuItemsToChart.count("All menu items"));
        chart->series(2 + (int)menu.size()).setHidden(true);
    }
    else
    {
        chart->series(1).setHidden(true);
        chart->series(2 + (int)menu.size()).setHidden(!menuItemsToChart.count("All menu items"));
    }
    
    int col = 2;
    for (std::vector<MenuItem>::iterator it = menu.begin(); it != menu.end(); ++it)
    {
        if (selectedIDRevQty == 0)
        {
            chart->series(col).setHidden(!menuItemsToChart.count(it->getName()));
            chart->series(col + (int)menu.size() + 1).setHidden(true);
        }
        else
        {
            chart->series(col).setHidden(true);
            chart->series(col + (int)menu.size() + 1).setHidden(!menuItemsToChart.count(it->getName()));
        }
        ++col;
    }
    chart->update();
    
    salesTemplate->removeWidget("legend");
    salesTemplate->bindWidget("legend", createLegendWidget());
    
    setChartYAxisRange(chart);
}

void SalesPage::setChartYAxisRange(Wt::Chart::WCartesianChart *chart)
{
    std::shared_ptr<Wt::Chart::WAbstractChartModel> model = chart->model();
    
    if (menuItemsToChart.count("All menu items"))
    {
        if (selectedIDRevQty == 0)
        {
            chart->axis(Wt::Chart::Axis::Y).setRange(0, std::max(10.0, maxSeriesRevenue["All menu items"] * 1.1));
        }
        else
        {
            chart->axis(Wt::Chart::Axis::Y).setRange(0, std::max(10.0, maxSeriesQuantity["All menu items"] * 1.1));
        }
        return;
    }
    
    double maxValue = 0;
    
    int col = 2;
    for (std::vector<MenuItem>::iterator it = menu.begin(); it != menu.end(); ++it)
    {
        if (menuItemsToChart.count(it->getName()))
        {
            double maxValueThisSeries;
            if (selectedIDRevQty == 0)
            {
                maxValueThisSeries = maxSeriesRevenue[it->getName()];
            }
            else
            {
                maxValueThisSeries = maxSeriesQuantity[it->getName()];
            }
            
            if (maxValueThisSeries > maxValue)
            {
                maxValue = maxValueThisSeries;
            }
        }
    }
    
    Wt::Chart::WAxis &yAxis = chart->axis(Wt::Chart::Axis::Y);
    yAxis.setRange(0, std::max(10.0, maxValue * 1.1));
}

void SalesPage::setYAxisTitle(Wt::WText *yAxisTitle)
{
    if (selectedIDRevQty == 0)
    {
        yAxisTitle->setText("Total Revenue ($)");
    }
    else
    {
        yAxisTitle->setText("Total Qty Sold (#)");
    }
}
