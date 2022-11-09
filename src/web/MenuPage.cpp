/*
    Author : River Wang
    Date   : 2022/11/08
*/

#include "MenuPage.hpp"

MenuPage::MenuPage(Wt::WApplication *instance) {
    std::vector<MenuItem> menuItems = DBHelper::getInstance().selectWhere(MenuItem());
    Wt::WContainerWidget *page = addWidget(std::make_unique<Wt::WContainerWidget>());

    for (std::vector<MenuItem>::iterator it = menuItems.begin(); it != menuItems.end(); it++) {
        page->addWidget(std::make_unique<MenuItemWidget>(it->getName(), std::to_string(it->getPrice()), "no description", MenuPage::orderMenuItem(*it, instance)));
    }
}

MenuPage::orderMenuItem(MenuItem item, Wt::WApplication *instance) {
    int numOrders = DBHelper::getInstance().selectWhere(OrderMaster()).size();
    OrderDetail orderDeets = OrderDetail(numOrders, item.getName(), quantity = 1);
    OrderMaster orderMast = OrderMaster(orderDeets.getOrderID());
    DBHelper::getInstance().insert(orderDeets);
    DBHelper::getInstance().insert(orderMast);

    // redirect to orders page
    instance->setInternalPath("/orders", true);
}