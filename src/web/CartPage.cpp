/*
    Author : River Wang
    Date   : 2022/11/19
*/

#include "CartPage.hpp"

CartPage::CartPage() {
    std::string sessionID = Wt::WApplication::instance()->sessionId();
    addStyleClass("list");

    std::vector<SqlCondition>
        conditions = {SqlCondition("sessionID", "=", sessionID)};
    std::vector<OrderMaster> orderMasters = DBHelper::getInstance().selectWhere(OrderMaster(), conditions);
    if (orderMasters.size() == 0) {
        addWidget(std::make_unique<Wt::WText>("No items in cart"));
        return;
    }

    OrderMaster currOrder = orderMasters[0];
    conditions = {SqlCondition("orderNumber", "=", currOrder.getOrderNumber())};
    std::vector<OrderDetail> orderDetails = DBHelper::getInstance().selectWhere(OrderDetail(), conditions);

    Wt::WContainerWidget *page = addWidget(std::make_unique<Wt::WContainerWidget>());

    for (std::vector<OrderDetail>::iterator it = orderDetails.begin(); it != orderDetails.end(); it++) {
        std::string itemName = it->getMenuItemName();
        int orderID = it->getOrderDetailID();
        int quantity = it->getQuantity();
        conditions = {SqlCondition("name", "=", itemName)};
        double itemPrice = DBHelper::getInstance().selectWhere(MenuItem(), conditions)[0].getPrice();
        double totalPrice = itemPrice * quantity;

        CartWidget *cartWidget = page->addWidget(std::make_unique<CartWidget>(itemName, itemPrice, quantity));

        auto addQuantity = [this, cartWidget, orderID] {
            cartWidget->updateQuantity(cartWidget->getQuantity() + 1);
            cartWidget->updateTotal();

            std::vector<SqlCondition> conditions = {SqlCondition("orderDetailID", "=", orderID)};
            std::vector<OrderDetail> orderDetails = DBHelper::getInstance().selectWhere(OrderDetail(), conditions);
            OrderDetail orderDetail = orderDetails[0];
            orderDetail.setQuantity(orderDetail.getQuantity() + 1);
            DBHelper::getInstance().update(orderDetail);
        };

        auto subtractQuantity = [this, cartWidget, orderID] {
            std::vector<SqlCondition> conditions = {SqlCondition("orderDetailID", "=", orderID)};
            std::vector<OrderDetail> orderDetails = DBHelper::getInstance().selectWhere(OrderDetail(), conditions);
            OrderDetail orderDetail = orderDetails[0];

            if (cartWidget->getQuantity() > 1) {
                cartWidget->updateQuantity(cartWidget->getQuantity() - 1);
                cartWidget->updateTotal();

                orderDetail.setQuantity(orderDetail.getQuantity() - 1);
                DBHelper::getInstance().update(orderDetail);
            } else {
                cartWidget->removeFromParent();
                DBHelper::getInstance().destroy(orderDetail);
            }
        };

        auto removeItem = [this, cartWidget, orderID] {
            cartWidget->removeFromParent();
            std::vector<SqlCondition> conditions = {SqlCondition("orderDetailID", "=", orderID)};
            std::vector<OrderDetail> orderDetails = DBHelper::getInstance().selectWhere(OrderDetail(), conditions);
            OrderDetail orderDetail = orderDetails[0];
            DBHelper::getInstance().destroy(orderDetail);
        };

        cartWidget->getAddPtr()->clicked().connect(addQuantity);
        cartWidget->getSubtractPtr()->clicked().connect(subtractQuantity);
        cartWidget->getRemovePtr()->clicked().connect(removeItem);
    }
}

CartPage::~CartPage() {
}