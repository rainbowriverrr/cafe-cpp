/*
    Author : River Wang
    Date   : 2022/10/27
*/

#include "MenuWidgets.hpp"

/*
    MenuItem
        Parameters:
            name: name of the item
            price: price of the item
            description: description of the item
            cartButton: pointer to the cart button (still not sure how to do this so i haven't implemented it yet)
    This method creates a MenuItem object, which is a container widget that contains the name, price, description, and cart button of an item
*/
MenuItemWidget::MenuItemWidget(const std::string &name, const double &price, const std::string &description)
    : WTemplate{tr("menu-item")} {
    std::string priceString;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << price;
    priceString = ss.str();

    name_ = bindWidget("name", std::make_unique<Wt::WText>(name));
    price_ = bindWidget("price", std::make_unique<Wt::WText>("$" + priceString));
    description_ = bindWidget("description", std::make_unique<Wt::WText>(description));
    cartButton_ = bindWidget("cart-button", std::make_unique<Wt::WPushButton>("Order"));
}

/*
    getCartPtr
        Return:
            WT::PushButton * : pointer to the cart button
    This method returns the pointer to the cart button, allowing you to connect it to a function
*/
Wt::WPushButton *MenuItemWidget::getCartPtr() {
    return cartButton_;
}
