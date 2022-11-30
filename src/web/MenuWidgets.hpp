/*
    Author : River Wang
    Date   : 2022/10/27
*/

#ifndef _MENUWIDGETS_HPP_
#define _MENUWIDGETS_HPP_

#include <Wt/WContainerWidget.h>
#include <Wt/WDoubleValidator.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>

#include <iomanip>
#include <iostream>
#include <string>

#include "Application.hpp"
#include "DBHelper.hpp"
#include "MenuItem.hpp"

class MenuItemWidget : public Wt::WTemplate {
   public:
    /**
     * @brief Construct a new Menu Item Widget object
     *
     * @param name
     * @param price
     * @param description
     */
    MenuItemWidget(const std::string &name, const double &price, const std::string &description);
    /**
     * @brief Get the Cart Ptr object
     *
     * @return Wt::WPushButton*
     */
    Wt::WPushButton *getCartPtr();

   private:
    /**
     * @brief WText widget representing the name of a menu item
     *
     */
    Wt::WText *name_;
    /**
     * @brief WText widget representing the price of a menu item
     */
    Wt::WText *price_;
    /**
     * @brief WText widget representing a menu item's description
     *
     */
    Wt::WText *description_;
    /**
     * @brief WPushButton representing the button pushed for a user to add to cart, can be replaced with a button to perform administrative actions.
     *
     */
    Wt::WPushButton *cartButton_;
};

class AddItemWidget : public Wt::WTemplate {
   public:
    /**
     * @brief Construct a new Add Item Widget object
     *
     */
    AddItemWidget();
    /**
     * @brief Get the Name of the menu item
     *
     * @return std::string
     */
    std::string getName();
    /**
     * @brief Get the Price of the menu item
     *
     * @return double
     */
    double getPrice();
    /**
     * @brief Get the Description of the menu item
     *
     * @return std::string
     */
    std::string getDescription();
    /**
     * @brief Get the pointer to the add item push button
     *
     * @return Wt::WPushButton*
     */
    Wt::WPushButton *getAddItemPtr();

   private:
    /**
     * @brief Field widget for inputting menu item name
     *
     */
    Wt::WLineEdit *name_;
    /**
     * @brief Field widget for inputting menu item price
     *
     */
    Wt::WLineEdit *price_;
    /**
     * @brief Field widget for inputting menu item description
     *
     */
    Wt::WTextArea *description_;
    /**
     * @brief Button to add item to database
     *
     */
    Wt::WPushButton *addItemButton_;
};

#endif
