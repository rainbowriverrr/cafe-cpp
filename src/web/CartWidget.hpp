/*
    Author : River Wang
    Date   : 2022/11/19
*/

#ifndef CartWidget_hpp
#define CartWidget_hpp

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

    int getQuantity();
    double getTotal();
    double getPrice();

   private:
    int iquantity;
    double dtotal;
    double dprice;
    Wt::WText *name_;
    Wt::WText *price_;
    Wt::WText *quantity_;
    Wt::WPushButton *removeButton_;
    Wt::WPushButton *addButton_;
    Wt::WPushButton *subtractButton_;
    Wt::WText *total_;
};

class CartTotal : public Wt::WTemplate {
   public:
    CartTotal(double);
    void addToTotal(double);
    void subFromTotal(double);
    Wt::WPushButton *getCheckoutPtr();
    ~CartTotal();

   private:
    void updateTotal();
    double dtotal;
    Wt::WText *total_;
    Wt::WPushButton *checkoutButton_;
};

#endif