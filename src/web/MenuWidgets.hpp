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
    MenuItemWidget(const std::string &name, const double &price, const std::string &description);
    Wt::WPushButton *getCartPtr();

   private:
    Wt::WText *name_;
    Wt::WText *price_;
    Wt::WText *description_;
    Wt::WPushButton *cartButton_;
};

class AddItemWidget : public Wt::WTemplate {
   public:
    AddItemWidget();
    std::string getName();
    double getPrice();
    std::string getDescription();
    Wt::WPushButton *getAddItemPtr();

   private:
    Wt::WLineEdit *name_;
    Wt::WLineEdit *price_;
    Wt::WTextArea *description_;
    Wt::WPushButton *addItemButton_;
};

#endif
