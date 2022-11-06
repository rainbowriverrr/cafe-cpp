//
//  MenuItem.cpp
//  DAL Test
//
//  Created by Julian Koksal on 2022-09-25.
//

#include "MenuItem.hpp"

MenuItem::MenuItem(std::string name, double price)
{
    this->tableName = "MenuItem";
    this->keys = { "name" };
    this->autoGeneratedKey = "";
    
    this->name = name;
    this->price = price;
}

MenuItem::~MenuItem()
{
    
}

std::map<std::string, std::any> MenuItem::toMap()
{
    std::map<std::string, std::any> mMap;
    mMap["name"] = name;
    mMap["price"] = price;
    
    return mMap;
}

Model * MenuItem::fromMap(std::map<std::string, std::any> mMap)
{
    std::string mName = std::any_cast<std::string>(mMap["name"]);
    double mPrice = std::any_cast<double>(mMap["price"]);
    MenuItem *model = new MenuItem(mName, mPrice);
    return model;
}

std::string MenuItem::getName()
{
    return name;
}

double MenuItem::getPrice()
{
    return price;
}

void MenuItem::setPrice(double price)
{
    this->price = price;
}