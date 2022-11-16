//
//  SalesPage.cpp
//
//  Created by Julian Koksal on 2022-11-13.
//

#include "SalesPage.hpp"

SalesPage::SalesPage()
{
    addStyleClass("list");
    addStyleClass("list-wide");
    
    salesTemplate = addNew<Wt::WTemplate>(tr("sales-chart"));
    
    numDaysToChart = 366;
    menuItemsToChart = { "All menu items" };
    menu = DBHelper::getInstance().selectWhere(MenuItem(), {}, "name");
    
    std::shared_ptr<Wt::WStandardItemModel> model = std::make_shared<Wt::WStandardItemModel>(numDaysToChart, menu.size() + 2);
    
    chart = salesTemplate->bindWidget("chart", createChartWidget(model));
    legend = salesTemplate->bindWidget("legend", createLegendWidget());
    
    dialog = addChild(createDialogWidget());
    
    btnOpenDialog = salesTemplate->bindWidget("btn-menu-item", createBtnOpenDialogWidget());
    btnOpenDialog->clicked().connect(this, &SalesPage::onBtnOpenDialogClick);
    
    updateModel(model.get());
    showSeries();
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
    chart->setPalette(std::make_shared<ChartPalette>());
    chart->setPanEnabled();
    
    // x axis
    chart->setXSeriesColumn(0);
    Wt::Chart::WAxis &xAxis = chart->axis(Wt::Chart::Axis::X);
    xAxis.setLabelFormat("yyyy-MM-dd");
    xAxis.setLabelFont(fontSmall);
    xAxis.setLabelInterval(7);
    xAxis.setScale(Wt::Chart::AxisScale::Date);
    xAxis.setRange(Wt::WDate::currentDate().toJulianDay() - numDaysToChart, Wt::WDate::currentDate().toJulianDay() - 1);
    xAxis.setZoomRange(Wt::WDate::currentDate().toJulianDay() - 10, Wt::WDate::currentDate().toJulianDay() - 1);
    xAxis.setMaximumZoomRange(10);
    
    // y axis
    Wt::Chart::WAxis &yAxis = chart->axis(Wt::Chart::Axis::Y);
    yAxis.setLabelFont(fontSmall);
    yAxis.setLabelFormat("%.0f");
    yAxis.setGridLinesEnabled(true);
    yAxis.setGridLinesPen(Wt::WPen(colourLightGray));
    
    // Series
    std::unique_ptr<Wt::Chart::WDataSeries> seriesAll = std::make_unique<Wt::Chart::WDataSeries>(1, Wt::Chart::SeriesType::Line);
    seriesAll->setMarker(Wt::Chart::MarkerType::Circle);
    chart->addSeries(std::move(seriesAll));
    
    int col = 2;
    for (std::vector<MenuItem>::iterator it = menu.begin(); it != menu.end(); it++)
    {
        std::unique_ptr<Wt::Chart::WDataSeries> series = std::make_unique<Wt::Chart::WDataSeries>(col, Wt::Chart::SeriesType::Line);
        series->setMarker(Wt::Chart::MarkerType::Circle);
        chart->addSeries(std::move(series));
        
        col++;
    }
    
    return chart;
}

std::unique_ptr<Wt::WContainerWidget> SalesPage::createLegendWidget()
{
    std::unique_ptr<Wt::WContainerWidget> legend = std::make_unique<Wt::WContainerWidget>();
    
    if (menuItemsToChart.empty())
    {
        return legend;
    }
    
    legend->addStyleClass("chart-legend");
    
    if (menuItemsToChart.count("All menu items"))
    {
        legend->addWidget(createLegendItemWidget("All menu items", ChartPalette::getColour(0)));
    }
    
    int i = 1;
    for (std::vector<MenuItem>::iterator it = menu.begin(); it != menu.end(); it++)
    {
        if (menuItemsToChart.count(it->getName()))
        {
            legend->addWidget(createLegendItemWidget(it->getName(), ChartPalette::getColour(i)));
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

std::unique_ptr<Wt::WDialog> SalesPage::createDialogWidget()
{
    std::unique_ptr<Wt::WDialog> dialog = std::make_unique<Wt::WDialog>();
    dialog->setTitleBarEnabled(false);
    dialog->setModal(false);
    dialog->setMovable(false);
    Wt::WContainerWidget *dialogContents = dialog->contents();
    dialogContents->addStyleClass("sales-dialog");
    
    dialogContents->addWidget(createDialogItemWidget("All menu items"));
    for (std::vector<MenuItem>::iterator it = menu.begin(); it != menu.end(); it++)
    {
        dialogContents->addWidget(createDialogItemWidget(it->getName()));
    }
    
    return dialog;
}

std::unique_ptr<Wt::WContainerWidget> SalesPage::createDialogItemWidget(std::string menuItemName)
{
    std::unique_ptr<Wt::WContainerWidget> item = std::make_unique<Wt::WContainerWidget>();
    
    Wt::WCheckBox *checkbox = item->addNew<Wt::WCheckBox>();
    checkbox->checked().connect([this, menuItemName] {
        menuItemsToChart.insert(menuItemName);
        showSeries();
    });
    checkbox->unChecked().connect([this, menuItemName] {
        menuItemsToChart.erase(menuItemName);
        showSeries();
    });
    
    if (menuItemsToChart.count(menuItemName))
    {
        checkbox->setChecked();
    }
    
    item->addNew<Wt::WText>("<label for='" + checkbox->id() + "'>" + menuItemName + "</label>");
    
    return item;
}

std::unique_ptr<Wt::WPushButton> SalesPage::createBtnOpenDialogWidget()
{
    std::unique_ptr<Wt::WPushButton> btn = std::make_unique<Wt::WPushButton>("Select menu items...");
    btn->addStyleClass("sales-select-menu-btn");
    
    return btn;
}

void SalesPage::onBtnOpenDialogClick()
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
    // Set values
    double maxValue = 10; // The highest value, used to determine the range of the y-axis.
    // Iterates from yesterday to numDaysToChart days ago.
    for (int daysAgo = 1; daysAgo <= numDaysToChart; daysAgo++)
    {
        Wt::WDate day = Wt::WDate::currentDate().addDays(daysAgo * -1);
        std::string start = day.toString("yyyy-MM-dd").toUTF8() + " 00:00:00.000"; // The start of the day.
        std::string end = day.addDays(1).toString("yyyy-MM-dd").toUTF8() + " 00:00:00.000"; // The start of the next day.
        
        model->setData(numDaysToChart - daysAgo, 0, day); // Sets the first column (x-axis).
        
        std::vector<OrderMaster> orders = DBHelper::getInstance().selectWhere(OrderMaster(), {
            SqlCondition("orderDate", ">=", start),
            SqlCondition("orderDate", "<", end),
            SqlCondition("isComplete", "=", true)
        });
        
        double totalSalesAllMenuItems = getTotalSalesFromOrders(orders);
        model->setData(numDaysToChart - daysAgo, 1, totalSalesAllMenuItems);
        
        int col = 2;
        for (std::vector<MenuItem>::iterator it = menu.begin(); it != menu.end(); it++)
        {
            double totalSales = getTotalSalesFromOrders(orders, it->getName());
            model->setData(numDaysToChart - daysAgo, col, totalSales);
            
            col++;
        }
        
        if (totalSalesAllMenuItems > maxValue)
        {
            maxValue = totalSalesAllMenuItems;
        }
    }
    
    chart->axis(Wt::Chart::Axis::Y).setRange(0, maxValue * 1.1);
}

double SalesPage::getTotalSalesFromOrders(std::vector<OrderMaster> orders, std::string menuItemName)
{
    double totalSales = 0;
    
    for (std::vector<OrderMaster>::iterator itOrders = orders.begin(); itOrders != orders.end(); itOrders++)
    {
        std::vector<SqlCondition> conditions = {
            SqlCondition("orderNumber", "=", itOrders->getOrderNumber())
        };
        if (!menuItemName.empty())
        {
            conditions.push_back(SqlCondition("menuItemName", "=", menuItemName));
        }
        
        std::vector<vOrderDetail> details = DBHelper::getInstance().selectWhere(vOrderDetail(), conditions);
        for (std::vector<vOrderDetail>::iterator itDetails = details.begin(); itDetails != details.end(); itDetails++)
        {
            totalSales += itDetails->getTotal();
        }
    }
    
    return totalSales;
}

void SalesPage::showSeries()
{
    chart->series(1).setHidden(!menuItemsToChart.count("All menu items"));
    
    int col = 2;
    for (std::vector<MenuItem>::iterator it = menu.begin(); it != menu.end(); it++)
    {
        chart->series(col).setHidden(!menuItemsToChart.count(it->getName()));
        col++;
    }
    chart->update();
    
    salesTemplate->removeWidget("legend");
    legend = salesTemplate->bindWidget("legend", createLegendWidget());
}
