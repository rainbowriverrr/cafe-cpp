/*
    Author : River Wang
    Date   : 2022/11/25
*/

#include "CartWidget.hpp"

CartWidget::CartWidget(std::string itemName, double itemPrice, int quantity) : Wt::WTemplate(Wt::WString::tr("cart-item")) {
    std::string priceString;
    std::string totalString;
    std::stringstream ss;

    name_ = bindNew<Wt::WText>("name");
    price_ = bindNew<Wt::WText>("price");
    total_ = bindNew<Wt::WText>("total");
    quantity_ = bindNew<Wt::WText>("quantity");
    removeButton_ = bindNew<Wt::WPushButton>("remove-button");
    addButton_ = bindNew<Wt::WPushButton>("add-button");
    subtractButton_ = bindNew<Wt::WPushButton>("subtract-button");

    updateQuantity(quantity);

    dprice = itemPrice;
    dtotal = dprice * quantity;

    updateTotal();

    name_->setText(itemName);
    ss << std::fixed << std::setprecision(2) << dprice;
    priceString = ss.str();

    price_->setText("$" + priceString);

    removeButton_->setText("Remove");
    addButton_->setText("+");
    subtractButton_->setText("-");
}

void CartWidget::updateQuantity(int quantity) {
    iquantity = quantity;
    quantity_->setText(std::to_string(iquantity));
}

void CartWidget::updateTotal() {
    dtotal = dprice * iquantity;
    std::string totalString;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << dtotal;
    totalString = ss.str();
    total_->setText("Subtotal = $" + totalString);
}

Wt::WPushButton *CartWidget::getRemovePtr() {
    return removeButton_;
}

Wt::WPushButton *CartWidget::getAddPtr() {
    return addButton_;
}

Wt::WPushButton *CartWidget::getSubtractPtr() {
    return subtractButton_;
}

CartWidget::~CartWidget() {
}

int CartWidget::getQuantity() {
    return iquantity;
}

double CartWidget::getTotal() {
    return dtotal;
}

double CartWidget::getPrice() {
    return dprice;
}

CartTotal::CartTotal(double total) : Wt::WTemplate(Wt::WString::tr("cart-total")) {
    dtotal = total;
    total_ = bindNew<Wt::WText>("total");
    updateTotal();

    checkoutButton_ = bindNew<Wt::WPushButton>("order-button");
    nameEdit_ = bindNew<Wt::WLineEdit>("name-edit");

    checkoutButton_->setText("Order Now!");
    nameEdit_->setPlaceholderText("Enter your name");
}

Wt::WPushButton *CartTotal::getCheckoutPtr() {
    return checkoutButton_;
}

std::string CartTotal::getName() {
    std::string nameStr = nameEdit_->text().toUTF8();

    if (nameStr == "") {
        nameStr = "Anonymous";
    }

    return nameStr;
}

void CartTotal::addToTotal(double total) {
    dtotal += total;
    updateTotal();
}

void CartTotal::subFromTotal(double total) {
    dtotal -= total;
    updateTotal();
}

void CartTotal::updateTotal() {
    std::string totalString;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << dtotal;
    totalString = ss.str();
    total_->setText("Total = $" + totalString);
}

CartTotal::~CartTotal() {
}