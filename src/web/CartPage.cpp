/*
    Author : River Wang
    Date   : 2022/11/19
*/

#include "CartPage.hpp"

CartPage::CartPage() {
    OrderMaster order = OrderMaster(0, "test", "2022-11-19 12:00:00", 0);
    std::vector<OrderDetail> orderDetails = DBHelper::getInstance().selectWhere(OrderDetail());
}