/*
    Author : River Wang
    Date   : 2022/11/08
*/

#include "MenuPage.hpp"

MenuPage::MenuPage() {
    std::vector<MenuItem> menuItems = DBHelper::getInstance().selectWhere(MenuItem());
    Wt::WContainerWidget *page = addWidget(std::make_unique<Wt::WContainerWidget>());
    addStyleClass("list");

    for (std::vector<MenuItem>::iterator it = menuItems.begin(); it != menuItems.end(); it++) {
        std::string name = it->getName();
        double price = it->getPrice();
        std::string description = it->getDescription();

        auto orderItem = [this, name] {
            time_t now = time(0);
            tm *localTime = std::localtime(&now);
            std::string formattedDate = std::to_string(localTime->tm_year + 1900) + "-" + std::to_string(localTime->tm_mon + 1) + "-" + std::to_string(localTime->tm_mday) + " " + std::to_string(localTime->tm_hour) + ":" + std::to_string(localTime->tm_min) + ":" + std::to_string(localTime->tm_sec);
            std::cout << formattedDate << std::endl;

            OrderMaster orderMast = OrderMaster(0, "test", formattedDate, 0);
            int orderNum = (int)DBHelper::getInstance().insert(orderMast);

            OrderDetail orderDeets = OrderDetail(0, orderNum, name, 1);
            DBHelper::getInstance().insert(orderDeets);

            Wt::WApplication::instance()->setInternalPath("/orders", true);
        };

        MenuItemWidget *itemWidget = page->addWidget(std::make_unique<MenuItemWidget>(name, price, description));

        // gets pointer to cart button and connects it to the orderItem function
        itemWidget->getCartPtr()->clicked().connect(orderItem);
    }
}

MenuPage::~MenuPage() {
}
