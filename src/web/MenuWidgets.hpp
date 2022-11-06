/*
    Author : River Wang
    Date   : 2022/10/27
*/

#ifndef _MENU_PAGE_HPP_
#define _MENU_PAGE_HPP_

#include <Wt/WContainerWidget.h>
#include <Wt/WIntValidator.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>

#include <string>

class MenuItem : public Wt::WTemplate {
   public:
    MenuItem(const std::string &name, const std::string &price, const std::string &description, const Wt::WPushButton *cartButton);
    Wt::WPushButton *getCartPtr();

   private:
    Wt::WText *name_;
    Wt::WText *price_;
    Wt::WText *description_;
    Wt::WPushButton *cartButton_;
};

#endif