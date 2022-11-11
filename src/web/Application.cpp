/*
    Author : River Wang
    Date   : 2022/10/31
*/

#include "Application.hpp"

Application::Application(const Wt::WEnvironment &env) : Wt::WApplication(env)
{
    setTitle("Cafe C++");

    useStyleSheet("resources/css/style.css");
    messageResourceBundle().use("resources/html/templates");

    internalPathChanged().connect(this, &Application::handleInternalPath);
    
    navbar = root()->addNew<NavbarWidget>();
    body = root()->addNew<Wt::WText>("Home Page");
}

Application::~Application()
{
    
}

void Application::handleInternalPath(const std::string &internalPath)
{
    if (internalPath == "/home")
    {
        root()->removeWidget(body);
        body = root()->addNew<Wt::WText>("Temp Home Page");
    }
    else if (internalPath == "/menu")
    {
        root()->removeWidget(body);
        body = root()->addNew<MenuPage>();
    }
    else if (internalPath == "/orders")
    {
        root()->removeWidget(body);
        body = root()->addNew<OrderListPage>();
    }
    else if (internalPath == "/inventory")
    {
        root()->removeWidget(body);
        body = root()->addNew<Wt::WText>("Temp Inventory Page");
    }
    else if (internalPath == "/cart")
    {
        root()->removeWidget(body);
        body = root()->addNew<Wt::WText>("Temp Cart Page");
    }
    else if (internalPath == "/login")
    {
        root()->removeWidget(body);
        body = root()->addNew<Wt::WText>("Temp Login Page");
    }
    else
    {
        setInternalPath("/home", true);
    }
}
