//
//  OrderListPage.hpp
//
//  Created by Julian Koksal on 2022-11-07.
//

#ifndef OrderListPage_hpp
#define OrderListPage_hpp

#include <string>
#include <chrono>

#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WPanel.h>
#include <Wt/WText.h>
#include <Wt/WString.h>

#include "DBHelper.hpp"
#include "IOHelper.hpp"
#include "OrderMaster.hpp"

class OrderListPage : public Wt::WContainerWidget
{
public:
    OrderListPage();
    ~OrderListPage();
    
    void panelOrderDetailsExpanded(Wt::WPanel *panel);
    void panelOrderDetailsCollapsed(Wt::WPanel *panel);
};

#endif /* OrderListPage_hpp */
