/*
    Author : River Wang
    Date   : 2022/10/27
*/

#ifndef _MENUWIDGETS_HPP
#define _MENUWIDGETS_HPP_

#include <Wt/WContainerWidget.h>
#include <Wt/WIntValidator.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>

#include <string>

class MenuItemWidget : public Wt::WTemplate {
   public:
    MenuItemWidget(const std::string &name, const std::string &price, const std::string &description, const Wt::WPushButton *cartButton);
    Wt::WPushButton *getCartPtr();

   private:
    Wt::WText *name_;
    Wt::WText *price_;
    Wt::WText *description_;
    Wt::WLineEdit *quantity_;
    Wt::WPushButton *cartButton_;
};

#endif