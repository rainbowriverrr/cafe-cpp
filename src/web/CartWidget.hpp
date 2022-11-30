/*
    Author : River Wang
    Date   : 2022/11/19
*/

#ifndef CartWidget_hpp
#define CartWidget_hpp

#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>

#include <iomanip>
#include <iostream>
#include <string>

class CartWidget : public Wt::WTemplate {
   public:
    /**
     * @brief Construct a new Cart Widget object
     *
     */
    CartWidget(std::string, double, int);

    /**
     * @brief update the quantity of the item
     *
     */
    void updateQuantity(int);

    /**
     * @brief update the total price of the item
     *
     */
    void updateTotal();

    /**
     * @brief Get the Remove Ptr object
     *
     * @return Wt::WPushButton*
     */
    Wt::WPushButton *getRemovePtr();
    /**
     * @brief Get the Add Ptr object
     *
     * @return Wt::WPushButton*
     */
    Wt::WPushButton *getAddPtr();
    /**
     * @brief Get the Subtract Ptr object
     *
     * @return Wt::WPushButton*
     */
    Wt::WPushButton *getSubtractPtr();

    /**
     * @brief Destroy the Cart Widget object
     *
     */
    ~CartWidget();

    /**
     * @brief Get the quantity of items
     *
     * @return int
     */
    int getQuantity();
    /**
     * @brief Get total price
     *
     * @return double
     */
    double getTotal();
    /**
     * @brief Get the price of a single item
     *
     * @return double
     */
    double getPrice();

   private:
    /**
     * @brief integer representation of quantity of an item
     *
     */
    int iquantity;
    /**
     * @brief double representation of total price of items
     *
     */
    double dtotal;
    /**
     * @brief double representation of price of an item
     *
     */
    double dprice;
    /**
     * @brief WText name widget
     *
     */
    Wt::WText *name_;
    /**
     * @brief WText price widget
     *
     */
    Wt::WText *price_;
    /**
     * @brief WText quantity widget.  The quantity of an item in the cart.
     *
     */
    Wt::WText *quantity_;
    /**
     * @brief WPushButton, remove button removes item from cart
     *
     */
    Wt::WPushButton *removeButton_;
    /**
     * @brief WPushButton, add button adds additional item to cart
     *
     */
    Wt::WPushButton *addButton_;
    /**
     * @brief WPushButton, subtract button subtracts an item from cart
     *
     */
    Wt::WPushButton *subtractButton_;
    /**
     * @brief WText total widget.  The total price of the current item(s) in the cart.
     *
     */
    Wt::WText *total_;
};

class CartTotal : public Wt::WTemplate {
   public:
    /**
     * @brief Construct a new Cart Total object
     *
     */
    CartTotal(double);
    /**
     * @brief adds to the total price
     *
     */
    void addToTotal(double);
    /**
     * @brief subtracts from the total price
     *
     */
    void subFromTotal(double);
    /**
     * @brief Gets the name of the item
     *
     * @return std::string
     */
    std::string getName();
    /**
     * @brief Get the Checkout Ptr object
     *
     * @return Wt::WPushButton*
     */
    Wt::WPushButton *getCheckoutPtr();
    /**
     * @brief Destroy the Cart Total object
     *
     */
    ~CartTotal();

   private:
    /**
     * @brief updates the total price (wrapper)
     *
     */
    void updateTotal();
    /**
     * @brief double representing the total price
     *
     */
    double dtotal;
    /**
     * @brief WText representing the total price
     *
     */
    Wt::WText *total_;
    /**
     * @brief LineEdit Widget for user name input.
     *
     */
    Wt::WLineEdit *nameEdit_;
    /**
     * @brief WPushButton representing the checkout button
     *
     */
    Wt::WPushButton *checkoutButton_;
};

#endif