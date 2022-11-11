//
//  OrderListPage.cpp
//
//  Created by Julian Koksal on 2022-11-07.
//

#include "OrderListPage.hpp"

OrderListPage::OrderListPage()
{
    // The orders not marked as complete.
    std::vector<OrderMaster> orders = DBHelper::getInstance().selectWhere(OrderMaster(), { SqlCondition("isComplete", "=", 0) }, "OrderDate");
    
    addStyleClass("list");
    
    listWidget = addNew<WContainerWidget>();
    
    if (orders.empty())
    {
        listWidget->addNew<Wt::WTemplate>(tr("order-list-empty"));
    }
    
    // Iterates the orders and adds them to list.
    for (std::vector<OrderMaster>::iterator it = orders.begin(); it != orders.end(); it++)
    {
        Wt::WTemplate *itemTemplate = listWidget->addNew<Wt::WTemplate>(tr("order-list-item"));
        
        // Complete order button
        
        Wt::WPushButton *completeBtn = itemTemplate->bindWidget("btn-complete", std::make_unique<Wt::WPushButton>("Complete Order"));
        completeBtn->setIcon("resources/images/check_circle.png");
        
        OrderMaster orderObj = *it;
        completeBtn->clicked().connect([this, itemTemplate, orderObj] { onCompleteOrderBtnClicked(itemTemplate, orderObj); });
        
        // Not a great solution, but Wt animations are bugged and do not seem to work on any browser.
        doJavaScript(itemTemplate->jsRef() + ".firstElementChild.addEventListener('transitionend', (e) => {"
                     + "if (e.target == " + itemTemplate->jsRef() + ".firstElementChild) " + itemTemplate->jsRef()
                     + ".style.display = 'none' });");
        
        // Binding text
        
        itemTemplate->bindWidget("txt-ordernum", std::make_unique<Wt::WText>((std::to_string(it->getOrderNumber()))));
        itemTemplate->bindWidget("txt-orderedby", std::make_unique<Wt::WText>(it->getOrderedBy()));
        itemTemplate->bindWidget("txt-orderdate", std::make_unique<Wt::WText>(it->getOrderDate().substr(0, 19)));
        
        // View items panel
        
        Wt::WPanel *panelOrderDetails = itemTemplate->bindWidget("panel-orderdetails", std::make_unique<Wt::WPanel>());
        
        panelOrderDetails->setTitle(Wt::WString("View Items"));
        panelOrderDetails->setCollapsible(true);
        panelOrderDetails->collapse();
        
        Wt::WAnimation animation(Wt::AnimationEffect::SlideInFromTop,
                                 Wt::TimingFunction::EaseOut,
                                 100);
        panelOrderDetails->setAnimation(animation);
        
        panelOrderDetails->expanded().connect([this, panelOrderDetails] { onPanelOrderDetailsExpanded(panelOrderDetails); });
        panelOrderDetails->collapsed().connect([this, panelOrderDetails] { onPanelOrderDetailsCollapsed(panelOrderDetails); });
        
        // Items table
        
        Wt::WTable *table = panelOrderDetails->setCentralWidget(std::make_unique<Wt::WTable>());
        table->addStyleClass("table-order-details");
        table->setHeaderCount(1);
        table->elementAt(0, 0)->addNew<Wt::WText>("Item");
        table->elementAt(0, 1)->addNew<Wt::WText>("Quantity");
        table->elementAt(0, 2)->addNew<Wt::WText>("Price");
        table->elementAt(0, 3)->addNew<Wt::WText>("Total");
        
        // Iterates the order details for this order.
        std::vector<vOrderDetail> details = DBHelper::getInstance()
            .selectWhere(vOrderDetail(), { SqlCondition("orderNumber", "=", it->getOrderNumber()) }, "menuItemName");
        double total = 0; // Keeps track of total price.
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

void OrderListPage::onCompleteOrderBtnClicked(Wt::WTemplate *itemTemplate, OrderMaster order)
{
    itemTemplate->addStyleClass("list-item-removed");
    //itemTemplate->animateHide(Wt::WAnimation(Wt::AnimationEffect::SlideInFromLeft | Wt::AnimationEffect::Fade, Wt::TimingFunction::Ease, 500));
    order.setIsComplete(true);
    DBHelper::getInstance().update(order);
    
    if (DBHelper::getInstance().selectWhere(OrderMaster(), { SqlCondition("isComplete", "=", 0) }).empty())
    {
        listWidget->addNew<Wt::WTemplate>(tr("order-list-empty"));
    }
}

void OrderListPage::onPanelOrderDetailsExpanded(Wt::WPanel *panel)
{
    panel->setTitle("Hide Items");
    panel->addStyleClass("panel-expanded");
}

void OrderListPage::onPanelOrderDetailsCollapsed(Wt::WPanel *panel)
{
    panel->setTitle("View Items");
    panel->removeStyleClass("panel-expanded");
}
