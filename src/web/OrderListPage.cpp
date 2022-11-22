//
//  OrderListPage.cpp
//
//  Created by Julian Koksal on 2022-11-07.
//

#include "OrderListPage.hpp"

OrderListPage::OrderListPage()
{
    addStyleClass("list");
    
    Wt::WContainerWidget *listContainer = addNew<WContainerWidget>();
    
    // The orders not marked as complete.
    std::vector<OrderMaster> orders = DBHelper::getInstance().selectWhere(OrderMaster(), { SqlCondition("isComplete", "=", 0) }, "OrderDate");
    
    if (orders.empty())
    {
        listContainer->addNew<Wt::WTemplate>(tr("order-list-empty"));
    }
    
    // Iterates the orders and adds them to list.
    for (std::vector<OrderMaster>::iterator it = orders.begin(); it != orders.end(); ++it)
    {
        listContainer->addWidget(createListItemWidget(listContainer, *it));
    }
}

OrderListPage::~OrderListPage()
{
    
}

void OrderListPage::onCompleteOrderBtnClicked(Wt::WTemplate *listItem, Wt::WContainerWidget *listContainer, OrderMaster order)
{
    listItem->addStyleClass("list-item-removed");
    // Doesn't work. Using CSS transitions and javascript instead.
    //itemTemplate->animateHide(Wt::WAnimation(Wt::AnimationEffect::SlideInFromLeft | Wt::AnimationEffect::Fade, Wt::TimingFunction::Ease, 500));
    order.setIsComplete(true);
    DBHelper::getInstance().update(order);
    
    if (DBHelper::getInstance().selectWhere(OrderMaster(), { SqlCondition("isComplete", "=", 0) }).empty())
    {
        listContainer->addNew<Wt::WTemplate>(tr("order-list-empty"));
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

std::unique_ptr<Wt::WTemplate> OrderListPage::createListItemWidget(Wt::WContainerWidget *listContainer, OrderMaster order)
{
    std::unique_ptr<Wt::WTemplate> item = std::make_unique<Wt::WTemplate>(tr("order-list-item"));
    
    // Complete order button
    
    Wt::WPushButton *completeBtn = item->bindWidget("btn-complete", std::make_unique<Wt::WPushButton>("Complete Order"));
    completeBtn->setIcon("resources/images/check_circle.png");
    
    Wt::WTemplate *itemRawPtr = item.get();
    completeBtn->clicked().connect([itemRawPtr, listContainer, order] { onCompleteOrderBtnClicked(itemRawPtr, listContainer, order); });
    
    // Not a great solution, but Wt animations are bugged and do not seem to work on any browser.
    doJavaScript(item->jsRef() + ".firstElementChild.addEventListener('transitionend', (e) => {"
                 + "if (e.target == " + item->jsRef() + ".firstElementChild) " + item->jsRef()
                 + ".style.display = 'none' });");
    
    // Binding text
    item->bindWidget("txt-ordernum", std::make_unique<Wt::WText>((std::to_string(order.getOrderNumber()))));
    item->bindWidget("txt-orderedby", std::make_unique<Wt::WText>(order.getOrderedBy()));
    item->bindWidget("txt-orderdate", std::make_unique<Wt::WText>(order.getOrderDate().substr(0, 19)));
    
    // View items panel
    Wt::WPanel *panelOrderDetails = item->bindWidget("panel-orderdetails", createDetailsPanelWidget(order.getOrderNumber()));
    
    return item;
}

std::unique_ptr<Wt::WPanel> OrderListPage::createDetailsPanelWidget(int orderNumber)
{
    std::unique_ptr<Wt::WPanel> panel = std::make_unique<Wt::WPanel>();
    
    panel->setTitle(Wt::WString("View Items"));
    panel->setCollapsible(true);
    panel->collapse();
    
    panel->setAnimation(Wt::WAnimation(Wt::AnimationEffect::SlideInFromTop, Wt::TimingFunction::EaseOut, 100));
    
    Wt::WPanel *panelRawPtr = panel.get();
    panel->expanded().connect([panelRawPtr] { onPanelOrderDetailsExpanded(panelRawPtr); });
    panel->collapsed().connect([panelRawPtr] { onPanelOrderDetailsCollapsed(panelRawPtr); });
    
    panel->setCentralWidget(createDetailsTableWidget(orderNumber));
    
    return panel;
}

std::unique_ptr<Wt::WTable> OrderListPage::createDetailsTableWidget(int orderNumber)
{
    std::unique_ptr<Wt::WTable> table = std::make_unique<Wt::WTable>();
    table->addStyleClass("table-order-details");
    table->setHeaderCount(1);
    table->elementAt(0, 0)->addNew<Wt::WText>("Item");
    table->elementAt(0, 1)->addNew<Wt::WText>("Quantity");
    table->elementAt(0, 2)->addNew<Wt::WText>("Price");
    table->elementAt(0, 3)->addNew<Wt::WText>("Total");
    
    // Iterates the order details for this order.
    std::vector<vOrderDetail> details = DBHelper::getInstance()
        .selectWhere(vOrderDetail(), { SqlCondition("orderNumber", "=", orderNumber) }, "menuItemName");
    double total = 0; // Keeps track of total price.
    int row = 1;
    for (std::vector<vOrderDetail>::iterator it = details.begin(); it != details.end(); ++it)
    {
        table->elementAt(row, 0)->addNew<Wt::WText>(it->getMenuItemName());
        table->elementAt(row, 1)->addNew<Wt::WText>(std::to_string(it->getQuantity()));
        table->elementAt(row, 2)->addNew<Wt::WText>(formatPrice(it->getPrice()));
        table->elementAt(row, 3)->addNew<Wt::WText>(formatPrice(it->getTotal()));
        total += it->getTotal();
        row++;
    }
    
    table->elementAt(row, 0)->addNew<Wt::WText>("Total");
    table->elementAt(row, 3)->addNew<Wt::WText>(formatPrice(total));
    
    return table;
}
