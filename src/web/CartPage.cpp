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
    conditions.push_back(SqlCondition("status", "=", "cart"));
    std::vector<OrderMaster> orderMasters = DBHelper::getInstance().selectWhere(OrderMaster(), conditions);
    if (orderMasters.size() == 0) {
        addWidget(std::make_unique<Wt::WText>("No items in cart"));
        return;
    }

    OrderMaster currOrder = orderMasters[0];
    conditions = {SqlCondition("orderNumber", "=", currOrder.getOrderNumber())};
    std::vector<OrderDetail> orderDetails = DBHelper::getInstance().selectWhere(OrderDetail(), conditions);

    Wt::WContainerWidget *page = addWidget(std::make_unique<Wt::WContainerWidget>());

    // Add checkout widget
    cartTotal = page->addWidget(std::make_unique<CartTotal>(0));
    Wt::WPushButton *checkoutbtn = cartTotal->getCheckoutPtr();
    auto checkout = [this, sessionID] {
        std::vector<SqlCondition>
            conditions = {SqlCondition("sessionID", "=", sessionID)};
        conditions.push_back(SqlCondition("status", "=", "cart"));
        std::vector<OrderMaster> orderMasters = DBHelper::getInstance().selectWhere(OrderMaster(), conditions);
        if (orderMasters.size() == 0) {
            return;
        } else {
            OrderMaster currOrder = orderMasters[0];
            currOrder.setStatus("ordered");
            currOrder.setOrderedBy(this->cartTotal->getName());
            DBHelper::getInstance().update(currOrder);
        }
        Wt::WApplication::instance()->setInternalPath("/orders", true);
    };
    checkoutbtn->clicked().connect(checkout);

    for (std::vector<OrderDetail>::iterator it = orderDetails.begin(); it != orderDetails.end(); it++) {
        std::string itemName = it->getMenuItemName();
        int orderID = it->getOrderDetailID();
        int quantity = it->getQuantity();
        conditions = {SqlCondition("name", "=", itemName)};
        double itemPrice = DBHelper::getInstance().selectWhere(MenuItem(), conditions)[0].getPrice();
        double totalPrice = itemPrice * quantity;

        cartTotal->addToTotal(totalPrice);

        CartWidget *cartWidget = page->addWidget(std::make_unique<CartWidget>(itemName, itemPrice, quantity));

        auto addQuantity = [this, cartWidget, orderID] {
            cartWidget->updateQuantity(cartWidget->getQuantity() + 1);
            cartWidget->updateTotal();

            getCartTotalPtr()->addToTotal(cartWidget->getPrice());

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

                getCartTotalPtr()->subFromTotal(cartWidget->getPrice());

                orderDetail.setQuantity(orderDetail.getQuantity() - 1);
                DBHelper::getInstance().update(orderDetail);
            } else {
                cartWidget->removeFromParent();
                DBHelper::getInstance().destroy(orderDetail);
                if (orderDetails.size() == 1) {
                    std::vector<SqlCondition> conditions = {SqlCondition("orderNumber", "=", orderDetail.getOrderNumber())};
                    std::vector<OrderMaster> orderMasters = DBHelper::getInstance().selectWhere(OrderMaster(), conditions);
                    OrderMaster orderMaster = orderMasters[0];
                    DBHelper::getInstance().destroy(orderMaster);

                    Wt::WApplication::instance()->setInternalPath("/menu", true);
                }
            }
        };

        auto removeItem = [this, cartWidget, orderID] {
            CartTotal *cartTotal = getCartTotalPtr();
            cartTotal->subFromTotal(cartWidget->getTotal());
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

CartTotal *CartPage::getCartTotalPtr() {
    return cartTotal;
}

CartPage::~CartPage() {
}