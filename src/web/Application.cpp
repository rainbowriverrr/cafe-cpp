/*
    Author : River Wang
    Date   : 2022/10/31
*/

#include "Application.hpp"

Application::Application(const Wt::WEnvironment &env): Wt::WApplication(env)
{
    setTitle("Cafe C++");
    
    useStyleSheet("resources/css/style.css");
    
    internalPathChanged().connect(this, &Application::handleInternalPath);
    
    page = root()->addNew<Wt::WContainerWidget>();
    
    navbar = page->addNew<NavbarWidget>();
    
    stack = page->addNew<Wt::WStackedWidget>();

    pageHome = stack->addNew<Wt::WText>("Home Page");
    pageMenu = stack->addNew<Wt::WText>("Menu Page");
    pageOrderList = stack->addNew<OrderListPage>();
}

Application::~Application()
{
    
}

void Application::handleInternalPath(const std::string &internalPath)
{
    if (internalPath == "/home")
    {
        stack->setCurrentWidget(pageHome);
    }
    else if (internalPath == "/menu")
    {
        stack->setCurrentWidget(pageMenu);
    }
    else if (internalPath == "/orders")
    {
        stack->setCurrentWidget(pageOrderList);
    }
    else
    {
        setInternalPath("/home", true);
    }
}

void Application::handleMenuPage()
{
    std::vector<MenuItem> menuItems = DBHelper::getInstance().selectWhere(MenuItem());
    for (int i = 0; i < menuItems.size(); i++) {
        stack->addNew<MenuItemWidget>(menuItems[i].getName(), std::to_string(menuItems[i].getPrice()), "description here", nullptr);
    }
}
