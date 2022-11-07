/*

    Author : River Wang
    Date   : 2022/10/27

*/

#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <Wt/WAnchor.h>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>
#include <Wt/WLink.h>
#include <Wt/WPanel.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WString.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "DBHelper.hpp"
#include "MenuItem.hpp"
#include "MenuWidgets.hpp"
#include "OrderMaster.hpp"

class Application : public Wt::WApplication {
   public:
    Application(const Wt::WEnvironment &env);
    void handleInternalPath(const std::string &internalPath);
    void handleMenuPage();

   private:
    Wt::WContainerWidget *page;

    Wt::WTemplate *navbar;
    Wt::WStackedWidget *stack;

    Wt::WText *pageHome;
    Wt::WText *pageMenu;
    Wt::WTemplate *pageOrders;

    DBHelper db;

    const Wt::WString readHtml(std::string fileName);
};

#endif
