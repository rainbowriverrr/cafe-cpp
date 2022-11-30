/*
    Author : River Wang
    Date   : 2022/11/08
*/

#include "MenuPage.hpp"

MenuPage::MenuPage() {
    std::vector<MenuItem> menuItems = DBHelper::getInstance().selectWhere(MenuItem());
    Wt::WContainerWidget *page = addWidget(std::make_unique<Wt::WContainerWidget>());
    addStyleClass("list");

    std::string sessionID = Wt::WApplication::instance()->sessionId();
    bool isAdmin = ((Application *)Application::instance())->getAuth()->IsLoggedIn();
    std::cout << "Is admin: " << isAdmin << std::endl;

    // if the user is an admin, show the add item widget
    if (isAdmin) {
        AddItemWidget *addWidget = page->addWidget(std::make_unique<AddItemWidget>());
        auto addItem = [this, addWidget] {
            std::string name = addWidget->getName();
            double price = addWidget->getPrice();
            std::string description = addWidget->getDescription();

            if (name == "" || price == 0 || description == "") {
                return;
            }

            MenuItem newItem = MenuItem(name, price, description);
            DBHelper::getInstance().insert(newItem);

            ((Application *)Application::instance())->handleInternalPath("/menu");
        };
        addWidget->getAddItemPtr()->clicked().connect(addItem);
    }

    for (std::vector<MenuItem>::iterator it = menuItems.begin(); it != menuItems.end(); it++) {
        std::string name = it->getName();
        double price = it->getPrice();
        std::string description = it->getDescription();

        auto orderItem = [this, name, sessionID] {
            time_t now = time(0);
            std::tm *ltm = localtime(&now);
            char time_str[20];
            std::strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", ltm);

            std::vector<SqlCondition> conditions = {SqlCondition("sessionID", "=", sessionID)};
            conditions.push_back(SqlCondition("status", "=", "cart"));
            std::vector<OrderMaster> orderMasters = DBHelper::getInstance().selectWhere(OrderMaster(), conditions);
            long orderNum = 0;
            if (orderMasters.size() == 0) {
                OrderMaster orderMast = OrderMaster(0, "test", time_str, "cart", sessionID);
                orderNum = DBHelper::getInstance().insert(orderMast);
            } else {
                orderNum = orderMasters[0].getOrderNumber();
            }

            conditions = {SqlCondition("orderNumber", "=", (int)orderNum)};
            conditions.push_back(SqlCondition("menuItemName", "=", name));
            std::vector<OrderDetail> orderDetails = DBHelper::getInstance().selectWhere(OrderDetail(), conditions);
            if (orderDetails.size() == 0) {
                OrderDetail orderDetail = OrderDetail(0, (int)orderNum, name, 1);
                DBHelper::getInstance().insert(orderDetail);
            } else {
                OrderDetail orderDetail = orderDetails[0];
                orderDetail.setQuantity(orderDetail.getQuantity() + 1);
                DBHelper::getInstance().update(orderDetail);
            }
        };

        auto removeItem = [this, name] {
            std::vector<SqlCondition> conditions = {SqlCondition("name", "=", name)};
            std::vector<MenuItem> menuItems = DBHelper::getInstance().selectWhere(MenuItem(), conditions);
            if (menuItems.size() == 0) {
                return;
            } else {
                MenuItem menuItem = menuItems[0];
                DBHelper::getInstance().destroy(menuItem);

                ((Application *)Application::instance())->handleInternalPath("/menu");
            }
        };

        MenuItemWidget *itemWidget = page->addWidget(std::make_unique<MenuItemWidget>(name, price, description));

        // gets pointer to cart button and connects it to the orderItem lambda if user is not logged in, otherwise connects it to the removeItem lambda
        if (isAdmin) {
            itemWidget->getCartPtr()->clicked().connect(removeItem);
        } else {
            itemWidget->getCartPtr()->clicked().connect(orderItem);
        }
    }
}

MenuPage::~MenuPage() {
}
