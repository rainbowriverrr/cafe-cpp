//
//  SalesPage.hpp
//

#ifndef SalesPage_hpp
#define SalesPage_hpp

#include <vector>
#include <set>
#include <algorithm>

#include <Wt/WTemplate.h>
#include <Wt/Chart/WCartesianChart.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WTableView.h>
#include <Wt/WDate.h>
#include <Wt/WFont.h>
#include <Wt/Chart/WChartPalette.h>
#include <Wt/WText.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WDialog.h>
#include <Wt/WPushButton.h>
#include <Wt/WCheckBox.h>

#include "ChartPalette.hpp"
#include "DBHelper.hpp"
#include "SqlCondition.hpp"
#include "OrderMaster.hpp"
#include "vOrderDetail.hpp"
#include "MenuItem.hpp"

/**
 * @brief Class representing the sales page widget.
 *
 * @author Julian Koksal
 * @date 2022-11-13
 */
class SalesPage : public Wt::WContainerWidget
{
public:
    SalesPage();
    ~SalesPage();
private:
    
    int numDaysToChart;
    
    std::vector<MenuItem> menu;
    
    std::set<std::string> menuItemsToChart;
    
    Wt::WTemplate *salesTemplate;
    
    Wt::Chart::WCartesianChart *chart;
    
    Wt::WContainerWidget *legend;
    
    Wt::WDialog *dialog;
    
    Wt::WPushButton *btnOpenDialog;
    
    std::unique_ptr<Wt::Chart::WCartesianChart> createChartWidget(std::shared_ptr<Wt::WStandardItemModel> model);
    
    std::unique_ptr<Wt::WContainerWidget> createLegendWidget();
    
    std::unique_ptr<Wt::WContainerWidget> createLegendItemWidget(std::string menuItemName, Wt::WColor colour);
    
    std::unique_ptr<Wt::WDialog> createDialogWidget();
    
    std::unique_ptr<Wt::WContainerWidget> createDialogItemWidget(std::string menuItemName);
    
    std::unique_ptr<Wt::WPushButton> createBtnOpenDialogWidget();
    
    void onBtnOpenDialogClick();
    
    void updateModel(Wt::WAbstractItemModel *model);
    
    double getTotalSalesFromOrders(std::vector<OrderMaster> orders, std::string menuItemName = "");
    
    void showSeries();
};

#endif /* SalesPage_hpp */
