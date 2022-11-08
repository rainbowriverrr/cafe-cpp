//
// Created by Sharon Nikritin on 2022-11-07.
//

#include "OrderDetail.h"

OrderDetail ::OrderDetail(int orderID, std::string menuItemName, int quantity) {
    this -> tableName = "OrderDetail";
    this -> keys = "orderID";
    this -> autoGeneratedKey = "orderID";

    this -> orderID = orderID;
    this -> orderName = orderName;
    this -> quantity = quantity;


}

OrderDetail :: ~OrderDetail() {

}

std::map<std::string, std::any> InventoryItem:: toMap()
{
    std::map<std::string, std::any> mMap;
    mMap["orderID"] = orderID;
    mMap["menuItemName"] = menuItemName;
    mMap["quantity"] = quantity;

    return mMap;
}

Model * InventoryItem::fromMap(std::map<std::string, std::any> mMap)
{

    int mID = std::any_cast<int>(mMap["orderID"]);
    std::string mName = std::any_cast<std::string>(mMap["menuItemName"]);
    int mQuantity = std::any_cast<int>(mMap["quantity"])
    MenuItem *model = new MenuItem(mID, mName, mQuantity);

    return model;
}

int OrderDetail ::getOrderID() {
    return orderID;
}

std::string OrderDetail ::getMenuItemName() {
    return menuItemName;
}

int OrderDetail ::getQuantity() {
    return quantity;
}

void OrderDetail ::setQuantity(int quantity) {
    this -> quantity = quantity;
}

void OrderDetail ::setMenuItemName(std::string menuItemName) {
    this -> menuItemName = menuItemName;
}

void OrderDetail ::setOrderID(int orderID) {
    this -> orderID = orderID;
}

