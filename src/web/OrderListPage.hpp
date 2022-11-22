//
//  OrderListPage.hpp
//

#ifndef OrderListPage_hpp
#define OrderListPage_hpp

#include <string>

#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WPanel.h>
#include <Wt/WTable.h>
#include <Wt/WPushButton.h>
#include <Wt/WLink.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WFlags.h>
#include <Wt/WAnimation.h>

#include "DBHelper.hpp"
#include "OrderMaster.hpp"
#include "vOrderDetail.hpp"
#include "Page.hpp"

/**
 * @brief Class representing the order list page widget.
 *
 * Displays a list of the active orders (not in progress or completed).
 * To customers, the list only shows the order number, name, and date.
 * To admins, the list also shows the order details and a complete button for each order.
 *
 * @author Julian Koksal
 * @date 2022-11-07
 */
class OrderListPage : public Page
{
public:
    /**
     * @brief Constructor.
     *
     * Creates the page widget and all of its contents.
     */
    OrderListPage();
    
    /**
     * @brief Destructor.
     *
     * Does nothing.
     */
    ~OrderListPage();
    
    /**
     * @brief Event handler for when the complete order button is clicked.
     *
     * Updates the order to complete and hides the list item with an animation.
     *
     * @param listItem the list item template widget
     * @param listContainer the list widget
     * @param order the order that the list item represents
     */
    static void onCompleteOrderBtnClicked(Wt::WTemplate *listItem, Wt::WContainerWidget *listContainer, OrderMaster order);
    
    /**
     * @brief Event handler for when the order details panel is expanded.
     *
     * Changes the text and plays the animation.
     *
     * @param panel The panel widget.
     */
    static void onPanelOrderDetailsExpanded(Wt::WPanel *panel);
    
    /**
     * @brief Event handler for when the order details panel is collapsed.
     *
     * Changes the text and plays the animation.
     *
     * @param panel The panel widget.
     */
    static void onPanelOrderDetailsCollapsed(Wt::WPanel *panel);
private:
    /**
     * @brief Creates and returns the list item widget and its contents.
     *
     * Represents one order in the list.
     * Shows the order number, name, and date to customers.
     * Also shows the order details and complete button to admins.
     *
     * @param listContainer the list widget
     * @param order the order that the list item represents
     * @return a unique ptr to the list item widget that was created
     */
    std::unique_ptr<Wt::WTemplate> createListItemWidget(Wt::WContainerWidget *listContainer, OrderMaster order);
    
    /**
     * @brief Creates and returns the order details dropdown panel widget.
     *
     * One of these widgets is put into the list item widget for each order.
     *
     * @param orderNumber the order number of the order that the list item represents
     * @return a unique ptr to the panel widget that was created
     */
    std::unique_ptr<Wt::WPanel> createDetailsPanelWidget(int orderNumber);
    
    /**
     * @brief Creates and returns the order details table that is contained in the panel.
     *
     * Shows a table of the order items, including their name, price, quantity, and total.
     * The last row of the table shows the total price for the whole order.
     *
     * @param orderNumber the order number of the details to show in the table
     * @return a unique ptr to the table widget that was created
     */
    std::unique_ptr<Wt::WTable> createDetailsTableWidget(int orderNumber);
};

#endif /* OrderListPage_hpp */
