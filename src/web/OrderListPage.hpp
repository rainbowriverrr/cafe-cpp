//
//  OrderListPage.hpp
//
//  Created by Julian Koksal on 2022-11-07.
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
#include <Wt/WText.h>
#include <Wt/WString.h>

#include "DBHelper.hpp"
#include "IOHelper.hpp"
#include "OrderMaster.hpp"
#include "vOrderDetail.hpp"

/**
 * Class representing the order list page widget.
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
    
    /**
     * Event handler for when the order details panel is expanded.
     * Changes the text and plays the animation.
     * @param panel The panel widget.
     */
    void panelOrderDetailsExpanded(Wt::WPanel *panel);
    
    /**
     * Event handler for when the order details panel is collapsed.
     * Changes the text and plays the animation.
     * @param panel The panel widget.
     */
    void panelOrderDetailsCollapsed(Wt::WPanel *panel);
};

#endif /* OrderListPage_hpp */
