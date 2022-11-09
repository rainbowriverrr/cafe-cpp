/*
    Author : River Wang
    Date   : 2022/11/08
*/

#include "MenuPage.hpp"

MenuPage::MenuPage() {
    std::vector<MenuItem> menuItems = DBHelper::getInstance().selectWhere(MenuItem());
    Wt::WContainerWidget *page = addWidget(std::make_unique<Wt::WContainerWidget>());

    for (std::vector<MenuItem>::iterator it = menuItems.begin(); it != menuItems.end(); it++) {
        auto orderItem = [this, it] {
            // int numOrders = DBHelper::getinstance().selectWhere(OrderMaster()).size();

            // OrderDetail orderDeets = OrderDetail(0, numOrders, it->getName(), 1);
            // OrderMaster orderMast = OrderMaster(orderDeets.getOrderID());
            // DBHelper::getInstance().insert(orderDeets);
            // DBHelper::getInstance().insert(orderMast);

            Wt::WApplication::instance()->setInternalPath("/orders", true);
        };

        MenuItemWidget *itemWidget = page->addWidget(std::make_unique<MenuItemWidget>(it->getName(), std::to_string(it->getPrice()), "no description"));

        // gets pointer to cart button and connects it to the orderItem function
        itemWidget->getCartPtr()->clicked().connect(orderItem);
    }
}

MenuPage::~MenuPage() {
}