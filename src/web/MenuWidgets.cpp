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
MenuItem::MenuItem(const std::string &name, const std::string &price, const std::string &description, const Wt::WPushButton *cartButton) {
    setContentAlignment(Wt::AlignmentFlag::Center);
    name_ = addWidget(std::make_unique<Wt::WText>(name));
    price_ = addWidget(std::make_unique<Wt::WText>(price));
    description_ = addWidget(std::make_unique<Wt::WText>(description));
    cartButton_ = addWidget(std::make_unique<Wt::WPushButton>("Add to Cart"));
}

/*
    getCartPtr
        Return:
            WT::PushButton * : pointer to the cart button
    This method returns the pointer to the cart button, allowing you to connect it to a function
*/
Wt::WPushButton *MenuItem::getCartPtr() {
    return cartButton_;
}