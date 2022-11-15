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
    
    Wt::WTemplate *salesTemplate = addNew<Wt::WTemplate>(tr("sales-chart"));
    
    numDaysToChart = 7;
    menuItemsToChart = { "Coffee", "Latte", "Cookie" };
    
    int numSeries = (int)menuItemsToChart.size() + 1;
    std::shared_ptr<Wt::WStandardItemModel> model = std::make_shared<Wt::WStandardItemModel>(numDaysToChart, numSeries + 1);
    
    chart = salesTemplate->bindWidget("chart", createChartWidget(model));
    
    updateModel(model.get());
    
    Wt::WContainerWidget *legend = salesTemplate->bindWidget("legend", createLegendWidget());
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
    Wt::WColor colourWhite = Wt::WColor(255, 255, 255);
    
    
    // Chart
    std::unique_ptr<Wt::Chart::WCartesianChart> chart = std::make_unique<Wt::Chart::WCartesianChart>();
    chart->setType(Wt::Chart::ChartType::Scatter);
    chart->setModel(model);
    
    // Styling
    chart->setTextPen(Wt::WPen(colourWhite));
    chart->setBackground(colourDarkGray);
    chart->setPlotAreaPadding(50, Wt::Side::Left | Wt::Side::Bottom | Wt::Side::Right);
    chart->resize("45em", "30em");
    chart->setPalette(std::make_shared<ChartPalette>());
    chart->setZoomEnabled();
    chart->setPanEnabled();
    
    // Axes
    chart->setAxisTitleFont(fontBold);
    
    // x axis
    chart->setXSeriesColumn(0);
    Wt::Chart::WAxis &xAxis = chart->axis(Wt::Chart::Axis::X);
    xAxis.setTitle("Date");
    xAxis.setTitleFont(fontBold);
    xAxis.setLabelFormat("yyyy-MM-dd");
    xAxis.setLabelFont(fontSmall);
    xAxis.setScale(Wt::Chart::AxisScale::Date);
    xAxis.setRange(Wt::WDate::currentDate().toJulianDay() - numDaysToChart, Wt::WDate::currentDate().toJulianDay() - 1);
    
    // y axis
    Wt::Chart::WAxis &yAxis = chart->axis(Wt::Chart::Axis::Y);
    yAxis.setTitle("Total Sales ($)");
    yAxis.setTitleFont(fontBold);
    yAxis.setTitleOrientation(Wt::Orientation::Vertical);
    yAxis.setLabelFont(fontSmall);
    yAxis.setLabelFormat("%.0f");
    yAxis.setGridLinesEnabled(true);
    yAxis.setGridLinesPen(Wt::WPen(colourDarkGray));
    
    // Series
    std::unique_ptr<Wt::Chart::WDataSeries> series = std::make_unique<Wt::Chart::WDataSeries>(1, Wt::Chart::SeriesType::Line);
    series->setMarker(Wt::Chart::MarkerType::Circle);
    chart->addSeries(std::move(series));
    
    for (int i = 0; i < menuItemsToChart.size(); i++)
    {
        std::unique_ptr<Wt::Chart::WDataSeries> series = std::make_unique<Wt::Chart::WDataSeries>(i + 2, Wt::Chart::SeriesType::Line);
        series->setMarker(Wt::Chart::MarkerType::Circle);
        chart->addSeries(std::move(series));
    }
    
    return chart;
}

std::unique_ptr<Wt::WContainerWidget> SalesPage::createLegendWidget()
{
    std::unique_ptr<Wt::WContainerWidget> legend = std::make_unique<Wt::WContainerWidget>();
    legend->addStyleClass("chart-legend");
    
    Wt::WContainerWidget *legendItem = legend->addNew<Wt::WContainerWidget>();
    legendItem->addStyleClass("flex-row");
    
    Wt::WCssDecorationStyle txtStyle = Wt::WCssDecorationStyle();
    txtStyle.setForegroundColor(ChartPalette::getColour(0));
    
    Wt::WText *lineTxt = legendItem->addNew<Wt::WText>("-&nbsp;");
    lineTxt->setDecorationStyle(txtStyle);
    
    legendItem->addNew<Wt::WText>("All menu items");

    for (int i = 0; i < menuItemsToChart.size(); i++)
    {
        legendItem = legend->addNew<Wt::WContainerWidget>();
        legendItem->addStyleClass("flex-row");
        
        Wt::WCssDecorationStyle txtStyle = Wt::WCssDecorationStyle();
        txtStyle.setForegroundColor(ChartPalette::getColour(i + 1));
        
        Wt::WText *lineTxt = legendItem->addNew<Wt::WText>("-&nbsp;");
        lineTxt->setDecorationStyle(txtStyle);
        
        legendItem->addNew<Wt::WText>(menuItemsToChart[i]);
    }
    
    return legend;
}

void SalesPage::updateModel(Wt::WAbstractItemModel *model)
{
    model->setHeaderData(1, std::string("All menu items"));
    
    for (int i = 0; i < menuItemsToChart.size(); i++)
    {
        model->setHeaderData(i + 2, menuItemsToChart[i]);
    }
    
    double maxValue = 10;
    for (int daysAgo = 1; daysAgo <= numDaysToChart; daysAgo++)
    {
        Wt::WDate day = Wt::WDate::currentDate().addDays(daysAgo * -1);
        std::string start = day.toString("yyyy-MM-dd").toUTF8() + " 00:00:00.000";
        std::string end = day.addDays(1).toString("yyyy-MM-dd").toUTF8() + " 00:00:00.000";
        
        model->setData(numDaysToChart - daysAgo, 0, day);
        
        double totalSales = 0;
        
        std::vector<OrderMaster> orders = DBHelper::getInstance().selectWhere(OrderMaster(), {
            SqlCondition("orderDate", ">=", start),
            SqlCondition("orderDate", "<", end),
            SqlCondition("isComplete", "=", true)
        });
        for (std::vector<OrderMaster>::iterator itOrders = orders.begin(); itOrders != orders.end(); itOrders++)
        {
            std::vector<SqlCondition> conditions = {
                SqlCondition("orderNumber", "=", itOrders->getOrderNumber())
            };
            
            std::vector<vOrderDetail> details = DBHelper::getInstance().selectWhere(vOrderDetail(), conditions);
            for (std::vector<vOrderDetail>::iterator itDetails = details.begin(); itDetails != details.end(); itDetails++)
            {
                totalSales += itDetails->getTotal();
            }
        }
        
        model->setData(numDaysToChart - daysAgo, 1, totalSales);
        
        if (totalSales > maxValue)
        {
            maxValue = totalSales;
        }
        
        for (int iMenu = 0; iMenu < menuItemsToChart.size(); iMenu++)
        {
            totalSales = 0;
            
            orders = DBHelper::getInstance().selectWhere(OrderMaster(), {
                SqlCondition("orderDate", ">=", start),
                SqlCondition("orderDate", "<", end),
                SqlCondition("isComplete", "=", true)
            });
            for (std::vector<OrderMaster>::iterator itOrders = orders.begin(); itOrders != orders.end(); itOrders++)
            {
                std::vector<SqlCondition> conditions = {
                    SqlCondition("orderNumber", "=", itOrders->getOrderNumber()),
                    SqlCondition("menuItemName", "=", menuItemsToChart[iMenu])
                };
                
                std::vector<vOrderDetail> details = DBHelper::getInstance().selectWhere(vOrderDetail(), conditions);
                for (std::vector<vOrderDetail>::iterator itDetails = details.begin(); itDetails != details.end(); itDetails++)
                {
                    totalSales += itDetails->getTotal();
                }
            }
            
            model->setData(numDaysToChart - daysAgo, iMenu + 2, totalSales);
        }
    }
    
    chart->axis(Wt::Chart::Axis::Y).setRange(0, maxValue * 1.1);
}
