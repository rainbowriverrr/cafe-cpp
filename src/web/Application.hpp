/*

    Author : River Wang
    Date   : 2022/10/27

*/

#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <string>
#include <vector>

#include <Wt/WString.h>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WPanel.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WAnchor.h>
#include <Wt/WLink.h>
#include <Wt/WImage.h>

#include "DBHelper.hpp"
#include "IOHelper.hpp"
#include "OrderMaster.hpp"
#include "NavbarWidget.hpp"
#include "OrderListPage.hpp"

class Application : public Wt::WApplication
{
public:
    Application(const Wt::WEnvironment &env);
    void handleInternalPath(const std::string &internalPath);
private:
    Wt::WContainerWidget *page;
    Wt::WStackedWidget *stack;
    
    NavbarWidget *navbar;
    
    Wt::WText *pageHome;
    Wt::WText *pageMenu;
    OrderListPage *pageOrderList;
};

#endif
