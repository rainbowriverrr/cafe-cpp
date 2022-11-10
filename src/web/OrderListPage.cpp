//
//  OrderListPage.cpp
//
//  Created by Julian Koksal on 2022-11-07.
//

#include "OrderListPage.hpp"

OrderListPage::OrderListPage()
{
    // The orders not marked as complete.
    std::vector<OrderMaster> orders = DBHelper::getInstance().selectWhere(OrderMaster(), { SqlCondition("isComplete", "=", 0) }, "OrderDate DESC");
    
    Wt::WTemplate *pageTemplate = addNew<Wt::WTemplate>(IOHelper::readHtml("page_orderList.html"));
    
    Wt::WContainerWidget *orderList = pageTemplate->bindWidget("w-order-list", std::make_unique<Wt::WContainerWidget>());
    
    if (orders.empty())
    {
        orderList->addNew<Wt::WTemplate>(IOHelper::readHtml("w_orderlistempty.html"));
    }
    
    // Iterates the orders and adds them to list.
    for (std::vector<OrderMaster>::iterator it = orders.begin(); it != orders.end(); it++)
    {
        Wt::WTemplate *item = orderList->addNew<Wt::WTemplate>(IOHelper::readHtml("w_OrderListItem.html"));
        
        Wt::WPushButton *completeBtn = item->bindWidget("btn-complete", std::make_unique<Wt::WPushButton>("Complete Order"));
        completeBtn->setIcon("resources/images/check_circle.png");
        
        OrderMaster orderMasterObj = *it;
        completeBtn->clicked().connect([orderList, item, orderMasterObj] {
            item->addStyleClass("w-order-list-item-completed");
            //completeBtn->animateHide(Wt::WAnimation(Wt::AnimationEffect::SlideInFromLeft | Wt::AnimationEffect::Fade, Wt::TimingFunction::Ease, 500));
            OrderMaster om = orderMasterObj;
            om.setIsComplete(true);
            DBHelper::getInstance().update(om);
            
            if (DBHelper::getInstance().selectWhere(OrderMaster(), { SqlCondition("isComplete", "=", 0) }).empty())
            {
                orderList->addNew<Wt::WTemplate>(IOHelper::readHtml("w_orderlistempty.html"));
            }
        });
        
        // Not a great solution, but Wt animations are bugged and do not seem to work on any browser.
        item->doJavaScript(item->jsRef() + ".firstElementChild.addEventListener('transitionend', (e) => {"
                           "if (e.target == " + item->jsRef() + ".firstElementChild) " + item->jsRef() + ".style.display = 'none' });");
        
        item->bindWidget("txt-ordernum", std::make_unique<Wt::WText>((std::to_string(it->getOrderNumber()))));
        item->bindWidget("txt-orderedby", std::make_unique<Wt::WText>(it->getOrderedBy()));
        item->bindWidget("txt-orderdate", std::make_unique<Wt::WText>(it->getOrderDate().substr(0, 19)));
        
        // Panel
        
        Wt::WPanel *panelOrderDetails = item->bindWidget("panel-orderdetails", std::make_unique<Wt::WPanel>());
        
        panelOrderDetails->setTitle(Wt::WString("View Items"));
        panelOrderDetails->setCollapsible(true);
        panelOrderDetails->collapse();
        
        Wt::WAnimation animation(Wt::AnimationEffect::SlideInFromTop,
                                 Wt::TimingFunction::EaseOut,
                                 100);
        panelOrderDetails->setAnimation(animation);
        
        panelOrderDetails->expanded().connect([this, panelOrderDetails] { panelOrderDetailsExpanded(panelOrderDetails); });
        panelOrderDetails->collapsed().connect([this, panelOrderDetails] { panelOrderDetailsCollapsed(panelOrderDetails); });
        
        Wt::WTable *table = panelOrderDetails->setCentralWidget(std::make_unique<Wt::WTable>());
        
        table->setWidth(Wt::WLength("100%"));
        table->setHeaderCount(1);
        table->elementAt(0, 0)->addNew<Wt::WText>("Item");
        table->elementAt(0, 1)->addNew<Wt::WText>("Quantity");
        table->elementAt(0, 2)->addNew<Wt::WText>("Price");
        table->elementAt(0, 3)->addNew<Wt::WText>("Total");
        
        std::vector<vOrderDetail> details = DBHelper::getInstance()
            .selectWhere(vOrderDetail(), { SqlCondition("orderNumber", "=", it->getOrderNumber()) }, "menuItemName");
        double total = 0;
        int row = 1;
        for (std::vector<vOrderDetail>::iterator it = details.begin(); it != details.end(); it++)
        {
            table->elementAt(row, 0)->addNew<Wt::WText>(it->getMenuItemName());
            table->elementAt(row, 1)->addNew<Wt::WText>(std::to_string(it->getQuantity()));
            table->elementAt(row, 2)->addNew<Wt::WText>(IOHelper::formatPrice(it->getPrice()));
            table->elementAt(row, 3)->addNew<Wt::WText>(IOHelper::formatPrice(it->getTotal()));
            total += it->getTotal();
            row++;
        }
        
        table->elementAt(row, 0)->addNew<Wt::WText>("Total");
        table->elementAt(row, 3)->addNew<Wt::WText>(IOHelper::formatPrice(total));
    }
}

OrderListPage::~OrderListPage()
{
    
}

void OrderListPage::panelOrderDetailsExpanded(Wt::WPanel *panel)
{
    panel->setTitle("Hide Items");
    panel->addStyleClass("expanded");
}

void OrderListPage::panelOrderDetailsCollapsed(Wt::WPanel *panel)
{
    panel->setTitle("View Items");
    panel->removeStyleClass("expanded");
}
