//
//  vOrderDetail.cpp
//  group8
//
//  Created by Julian Koksal on 2022-11-08.
//

#include "vOrderDetail.hpp"

vOrderDetail::vOrderDetail(int orderDetailID, int orderNumber, std::string menuItemName, int quantity, double price, double total)
{
    this->tableName = "vOrderDetail";
    this->keys = { "orderDetailID" };
    this->autoGeneratedKey = "orderDetailID";
    
    this->orderDetailID = orderDetailID;
    this->orderNumber = orderNumber;
    this->menuItemName = menuItemName;
    this->quantity = quantity;
    this->price = price;
    this->total = total;
}

vOrderDetail::~vOrderDetail()
{
    
}

std::map<std::string, std::any> vOrderDetail:: toMap() const
{
    std::map<std::string, std::any> mMap;
    mMap["orderDetailID"] = orderDetailID;
    mMap["orderNumber"] = orderNumber;
    mMap["menuItemName"] = menuItemName;
    mMap["quantity"] = quantity;
    mMap["price"] = price;
    mMap["total"] = total;

    return mMap;
}

Model * vOrderDetail::fromMap(std::map<std::string, std::any> mMap) const
{
    int mOrderDetailID = std::any_cast<int>(mMap["orderDetailID"]);
    int mOrderNumber = std::any_cast<int>(mMap["orderNumber"]);
    std::string mName = std::any_cast<std::string>(mMap["menuItemName"]);
    int mQuantity = std::any_cast<int>(mMap["quantity"]);
    int mPrice = std::any_cast<double>(mMap["price"]);
    int mTotal = std::any_cast<double>(mMap["total"]);
    vOrderDetail *model = new vOrderDetail(mOrderDetailID, mOrderNumber, mName, mQuantity, mPrice, mTotal);

    return model;
}

int vOrderDetail::getOrderDetailID() {
    return orderDetailID;
}

int vOrderDetail::getOrderNumber() {
    return orderNumber;
}

std::string vOrderDetail::getMenuItemName() {
    return menuItemName;
}

int vOrderDetail::getQuantity() {
    return quantity;
}

double vOrderDetail::getPrice() {
    return price;
}

double vOrderDetail::getTotal()
{
    return total;
}
