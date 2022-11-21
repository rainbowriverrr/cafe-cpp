//
//  SalesPage.hpp
//

#ifndef SalesPage_hpp
#define SalesPage_hpp

#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include <Wt/WTemplate.h>
#include <Wt/Chart/WCartesianChart.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WTableView.h>
#include <Wt/WDate.h>
#include <Wt/WFont.h>
#include <Wt/WPen.h>
#include <Wt/WBrush.h>
#include <Wt/WText.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WDialog.h>
#include <Wt/WPushButton.h>
#include <Wt/WButtonGroup.h>
#include <Wt/WRadioButton.h>
#include <Wt/WCheckBox.h>

#include "DBHelper.hpp"
#include "SqlCondition.hpp"
#include "OrderMaster.hpp"
#include "vOrderDetail.hpp"
#include "vOrderSales.hpp"
#include "MenuItem.hpp"

/**
 * @brief Class representing the sales page widget.
 *
 * This page displays a chart showing the total sales from orders over time.
 * The chart can be filtered by menu item to compare the sales of specific items.
 *
 * @author Julian Koksal
 * @date 2022-11-13
 */
class SalesPage : public Wt::WContainerWidget
{
public:
    /**
     * @brief Constructor.
     *
     * Creates the page widget and adds all the content widgets.
     */
    SalesPage();
    
    /**
     * @brief Destructor.
     *
     * Does nothing.
     */
    ~SalesPage();
private:
    /**
     * @brief The number of days that will be charted. Default 366.
     */
    static const int NUM_DAYS_TO_CHART;
    
    /**
     * @brief Palette that the chart will use to colour the different series.
     */
    static const std::vector<Wt::WColor> COLOUR_PALETTE;
    
    /**
     * @brief The menu as retreived from the database.
     */
    std::vector<MenuItem> menu;
    
    /**
     * @brief The names of menu items which are currently visible in the chart.
     */
    std::set<std::string> menuItemsToChart;
    
    /**
     * @brief The selected ID of the revenue-quanity button group. 0 is revenue, 1 is quantity.
     */
    int selectedIDRevQty;
    
    /**
     * @brief Maps menu item names to the maximum value of its data series. Used to determine the chart y-axis range.
     */
    std::map<std::string, double> maxSeriesRevenue;
    
    /**
     * @brief Maps menu item names to the maximum value of its data series. Used to determine the chart y-axis range.
     */
    std::map<std::string, int> maxSeriesQuantity;
    
    /**
     * @brief Creates and returns the chart widget.
     *
     * @param model the data model for the chart
     * @return a unique ptr to the chart widget that was created
     */
    std::unique_ptr<Wt::Chart::WCartesianChart> createChartWidget(std::shared_ptr<Wt::WStandardItemModel> model);
    
    /**
     * @brief Creates and returns the legend widget.
     *
     * Has a column of legend item widgets.
     *
     * @return a unique ptr to the legend widget that was created
     */
    std::unique_ptr<Wt::WContainerWidget> createLegendWidget();
    
    /**
     * @brief Creates and returns a legend item widget.
     *
     * Each legend item is a coloured line and a label (e.g. "- Coffee").
     *
     * @param menuItemName the name of the menu item that this line of the legend is for
     * @param colour the colour of the line, should match the colour of the data series
     * @return a unique ptr to the legend item widget that was created
     */
    std::unique_ptr<Wt::WContainerWidget> createLegendItemWidget(std::string menuItemName, Wt::WColor colour);
    
    /**
     * @brief Creates and returns the revenue-quantity button group widget.
     *
     * Contains two radio buttons, lablled Rev($) and Qty(#), used to switch which value is plotted by the chart.
     *
     * @param chart the chart widget
     * @param salesTemplate the page template widget
     * @param yAxisTitle the y-axis title text widget
     * @return a unique ptr to the container widget that holds the button group
     */
    std::unique_ptr<Wt::WContainerWidget> createBtnGroupRevQty(Wt::Chart::WCartesianChart *chart, Wt::WTemplate *salesTemplate, Wt::WText *yAxisTitle);
    
    /**
     * @brief Creates and returns the dialog widget.
     *
     * Has a column of dialog item widgets.
     *
     * @param chart the chart widget
     * @param salesTemplate the page template widget
     * @return a unique ptr to the dialog widget that was created
     */
    std::unique_ptr<Wt::WDialog> createDialogWidget(Wt::Chart::WCartesianChart *chart, Wt::WTemplate *salesTemplate);
    
    /**
     * @brief Creates and returns a dialog item widget.
     *
     * Each dialog item is a checkbox with a label, where the label is the name of the menu item.
     * Used to show/hide series on the chart.
     *
     * @param chart the chart widget
     * @param salesTemplate the page template widget
     * @param menuItemName the name of the menu item, used for the label
     * @return a unique ptr to the dialog item widget that was created
     */
    std::unique_ptr<Wt::WContainerWidget> createDialogItemWidget(Wt::Chart::WCartesianChart *chart, Wt::WTemplate *salesTemplate, std::string menuItemName);
    
    /**
     * @brief Creates and returns the open dialog button widget.
     *
     * No event handler is attached yet.
     *
     * @return a unique ptr to the button widget that was created
     */
    std::unique_ptr<Wt::WPushButton> createBtnOpenDialogWidget();
    
    /**
     * @brief Event handler for the open dialog button.
     *
     * Shows/hides the dialog.
     *
     * @param dialog the dialog widget
     * @param btnOpenDialog the open dialog button widget
     */
    void onBtnOpenDialogClick(Wt::WDialog *dialog, Wt::WPushButton *btnOpenDialog);
    
    /**
     * @brief Updates the given model with order sales data from the database.
     *
     * The first column is given the dates data, going from 366 days ago to yesterday.
     * The second column is given the total sales data for all menu items.
     * The following columns are the total sales data for each menu item.
     *
     * @param model the model to populate with data
     */
    void updateModel(Wt::WAbstractItemModel *model);
    
    /**
     * @brief Shows/hides the chart series and associated legend items based on menuItemsToChart.
     *
     * @param chart the chart widget
     * @param salesTemplate the page template widget
     */
    void showSeries(Wt::Chart::WCartesianChart *chart, Wt::WTemplate *salesTemplate);
    
    /**
     * @brief Sets the range of the chart y-axis to fit the data.
     *
     * The range is set to be from 0 to 1.1 times the highest value of the series that are currently visible.
     *
     * @param chart the chart widget
     */
    void setChartYAxisRange(Wt::Chart::WCartesianChart *chart);
    
    /**
     * @brief Sets the y-axis title based on selectedIDRevQty.
     *
     * @param yAxisTitle the y-axis title text widget
     */
    void setYAxisTitle(Wt::WText *yAxisTitle);
};

#endif /* SalesPage_hpp */
