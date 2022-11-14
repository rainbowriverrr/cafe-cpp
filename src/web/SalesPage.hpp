//
//  SalesPage.hpp
//

#ifndef SalesPage_hpp
#define SalesPage_hpp

#include <vector>

#include <Wt/WTemplate.h>
#include <Wt/Chart/WCartesianChart.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WTableView.h>
#include <Wt/WDate.h>
#include <Wt/WFont.h>
#include <Wt/Chart/WChartPalette.h>

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
    void updateModel(Wt::WAbstractItemModel *model, int numDays, std::vector<std::string> menuItems);
};

#endif /* SalesPage_hpp */
