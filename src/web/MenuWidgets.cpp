/*
    Author : River Wang
    Date   : 2022/10/27
*/

#include "MenuWidgets.hpp"

MenuItem::MenuItem(const std::string &name, const std::string &price, const std::string &description, const Wt::WPushButton *cartButton) {
    setContentAlignment(Wt::AlignmentFlag::Center);
    name_ = addWidget(std::make_unique<Wt::WText>(name));
    price_ = addWidget(std::make_unique<Wt::WText>(price));
    description_ = addWidget(std::make_unique<Wt::WText>(description));
    cartButton_ = addWidget(std::make_unique<Wt::WPushButton>("Add to Cart"));
}

Wt::WPushButton *MenuItem::getCartPtr() {
    return cartButton_;
}