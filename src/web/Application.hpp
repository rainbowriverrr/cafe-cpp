/*

    Author : River Wang
    Date   : 2022/10/27

*/

#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <iostream>
#include <fstream>

#include <Wt/WString.h>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WAnchor.h>
#include <Wt/WLink.h>
#include <Wt/WImage.h>

class Application : public Wt::WApplication
{
public:
    Application(const Wt::WEnvironment &env);
    void handleInternalPath(const std::string &internalPath);
private:
    Wt::WContainerWidget *page;
    
    Wt::WTemplate *navbar;
    Wt::WStackedWidget *stack;
    
    Wt::WText *pageHome;
    Wt::WText *pageMenu;
    Wt::WText *pageOrders;
    
    const Wt::WString readHtml(std::string fileName);
};

#endif
