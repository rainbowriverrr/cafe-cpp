//
//  SalesPage.hpp
//

#ifndef SalesPage_hpp
#define SalesPage_hpp

#include <vector>
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

#include "ChartPalette.hpp"
#include "DBHelper.hpp"
#include "SqlCondition.hpp"
#include "OrderMaster.hpp"
#include "vOrderDetail.hpp"

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
    
    std::vector<std::string> menuItemsToChart;
    
    Wt::Chart::WCartesianChart *chart;
    
    std::unique_ptr<Wt::Chart::WCartesianChart> createChartWidget(std::shared_ptr<Wt::WStandardItemModel> model);
    
    std::unique_ptr<Wt::WContainerWidget> createLegendWidget();
    
    void updateModel(Wt::WAbstractItemModel *model);
};

#endif /* SalesPage_hpp */
