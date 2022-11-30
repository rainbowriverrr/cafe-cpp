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
    bool isLoggedIn = ((Application *)Application::instance())->getAuth()->IsLoggedIn();
    std::string priceString;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << price;
    priceString = ss.str();

    name_ = bindWidget("name", std::make_unique<Wt::WText>(name));
    price_ = bindWidget("price", std::make_unique<Wt::WText>("$" + priceString));
    description_ = bindWidget("description", std::make_unique<Wt::WText>(description));

    if (isLoggedIn) {
        cartButton_ = bindWidget("cart-button", std::make_unique<Wt::WPushButton>("Remove Item"));
    } else {
        cartButton_ = bindWidget("cart-button", std::make_unique<Wt::WPushButton>("Add to Cart"));
    }
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

AddItemWidget::AddItemWidget() : WTemplate{tr("add-item")} {
    auto priceEdit = std::make_unique<Wt::WLineEdit>();
    priceEdit->setValidator(std::make_shared<Wt::WDoubleValidator>(0, 1000));

    name_ = bindWidget("name", std::make_unique<Wt::WLineEdit>());
    price_ = bindWidget("price", std::move(priceEdit));
    description_ = bindWidget("description", std::make_unique<Wt::WTextArea>());
    addItemButton_ = bindWidget("add-item-button", std::make_unique<Wt::WPushButton>("Add Item"));

    description_->setColumns(30);
    description_->setRows(4);

    name_->setPlaceholderText("Name");
    price_->setPlaceholderText("Price");
    description_->setPlaceholderText("Description");
}

Wt::WPushButton *AddItemWidget::getAddItemPtr() {
    return addItemButton_;
}

std::string AddItemWidget::getName() {
    if (name_->text().toUTF8() == "") {
        name_->setPlaceholderText("Name Required");
    }
    return name_->text().toUTF8();
}

double AddItemWidget::getPrice() {
    if (price_->validate() != Wt::ValidationState::Valid) {
        price_->setPlaceholderText("NaN");
        price_->setText("");
        return 0;
    }

    std::string priceString = price_->text().toUTF8();

    if (priceString == "" || priceString == ".") {
        return 0;
    }

    return std::stod(priceString);
}

std::string AddItemWidget::getDescription() {
    if (description_->text().toUTF8() == "") {
        description_->setPlaceholderText("Description Required");
    }
    return description_->text().toUTF8();
}
