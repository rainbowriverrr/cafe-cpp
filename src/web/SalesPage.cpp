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
    
    std::vector<std::string> menuItems = { "Coffee", "Latte" };
    
    std::shared_ptr<Wt::WStandardItemModel> model = std::make_shared<Wt::WStandardItemModel>(10, 2);
    updateModel(model.get(), 10, menuItems);
    
    Wt::Chart::WCartesianChart *chart = salesTemplate->bindWidget("chart", std::make_unique<Wt::Chart::WCartesianChart>());
    
    chart->setModel(model);
    chart->setType(Wt::Chart::ChartType::Scatter);
    
    chart->setTextPen(Wt::WPen(colourWhite));
    chart->setBackground(colourDarkGray);
    
    chart->setLegendEnabled(true);
    chart->setLegendStyle(fontSmall, Wt::WPen(Wt::PenStyle::None), Wt::WBrush(Wt::BrushStyle::None));
    
    chart->setAxisTitleFont(fontBold);
    
    chart->setXSeriesColumn(0);
    chart->axis(Wt::Chart::Axis::X).setTitle("Date");
    chart->axis(Wt::Chart::Axis::X).setTitleFont(fontBold);
    chart->axis(Wt::Chart::Axis::X).setScale(Wt::Chart::AxisScale::Date);
    chart->axis(Wt::Chart::Axis::X).setLabelFormat("yyyy-MM-dd");
    chart->axis(Wt::Chart::Axis::X).setLabelFont(fontSmall);
    
    chart->axis(Wt::Chart::Axis::Y).setTitle("Total Sales ($)");
    chart->axis(Wt::Chart::Axis::Y).setTitleFont(fontBold);
    chart->axis(Wt::Chart::Axis::Y).setTitleOrientation(Wt::Orientation::Vertical);
    chart->axis(Wt::Chart::Axis::Y).setLabelFont(fontSmall);
    chart->axis(Wt::Chart::Axis::Y).setLabelFormat("%.0f");
    chart->axis(Wt::Chart::Axis::Y).setGridLinesEnabled(true);
    chart->axis(Wt::Chart::Axis::Y).setGridLinesPen(Wt::WPen(colourDarkGray));
    
    chart->setPlotAreaPadding(50, Wt::Side::Left | Wt::Side::Bottom);
    chart->setPlotAreaPadding(200, Wt::Side::Right);

    if (menuItems.empty())
    {
        std::unique_ptr<Wt::Chart::WDataSeries> series = std::make_unique<Wt::Chart::WDataSeries>(1, Wt::Chart::SeriesType::Line);
        chart->addSeries(std::move(series));
    }
    else
    {
        for (int i = 0; i < menuItems.size(); i++)
        {
            std::unique_ptr<Wt::Chart::WDataSeries> series = std::make_unique<Wt::Chart::WDataSeries>(i + 1, Wt::Chart::SeriesType::Line);
            chart->addSeries(std::move(series));
        }
    }

    chart->resize("55em", "30em");
}

SalesPage::~SalesPage()
{
    
}

void SalesPage::updateModel(Wt::WAbstractItemModel *model, int numDays, std::vector<std::string> menuItems)
{
    if (menuItems.empty())
    {
        model->setHeaderData(1, "All menu items");
    }
    else
    {
//        for (int i = 0; i < menuItems.size(); i++)
//        {
//            model->setHeaderData(i + 1, menuItems[i]);
//        }
    }
    
    for (int i = 0; i < numDays; i++)
    {
        Wt::WDate day = Wt::WDate::currentDate().addDays(i * -1);
        std::string start = day.toString("yyyy-MM-dd").toUTF8() + " 00:00:00.000";
        std::string end = day.addDays(1).toString("yyyy-MM-dd").toUTF8() + " 00:00:00.000";
        
        double totalSales = 0;
        
        std::vector<OrderMaster> orders = DBHelper::getInstance().selectWhere(OrderMaster(), {
            SqlCondition("orderDate", ">=", start),
            SqlCondition("orderDate", "<", end),
            SqlCondition("isComplete", "=", false)
        });
        for (std::vector<OrderMaster>::iterator itOrders = orders.begin(); itOrders != orders.end(); itOrders++)
        {
            std::vector<SqlCondition> conditions = { SqlCondition("orderNumber", "=", itOrders->getOrderNumber()) };
            
            std::vector<vOrderDetail> details = DBHelper::getInstance().selectWhere(vOrderDetail(), conditions);
            for (std::vector<vOrderDetail>::iterator itDetails = details.begin(); itDetails != details.end(); itDetails++)
            {
                totalSales += itDetails->getTotal();
            }
        }
        
        model->setData(numDays - 1 - i, 0, day);
        model->setData(numDays - 1 - i, 1, totalSales);
    }
}
