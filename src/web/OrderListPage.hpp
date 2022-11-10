//
//  OrderListPage.hpp
//

#ifndef OrderListPage_hpp
#define OrderListPage_hpp

#include <string>
#include <sstream>

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
#include "IOHelper.hpp"
#include "OrderMaster.hpp"
#include "vOrderDetail.hpp"

/**
 * @brief Class representing the order list page widget.
 * @author Julian Koksal
 * @date 2022-11-07
 */
class OrderListPage : public Wt::WContainerWidget
{
public:
    /**
     * Constructor.
     */
    OrderListPage();
    
    /**
     * Destructor.
     */
    ~OrderListPage();
    
    void onCompleteOrderBtnClicked(Wt::WTemplate *itemTemplate, OrderMaster order);
    
    /**
     * @brief Event handler for when the order details panel is expanded.
     * Changes the text and plays the animation.
     * @param panel The panel widget.
     */
    void onPanelOrderDetailsExpanded(Wt::WPanel *panel);
    
    /**
     * @brief Event handler for when the order details panel is collapsed.
     * Changes the text and plays the animation.
     * @param panel The panel widget.
     */
    void onPanelOrderDetailsCollapsed(Wt::WPanel *panel);
private:
    Wt::WContainerWidget *listWidget;
};

#endif /* OrderListPage_hpp */
