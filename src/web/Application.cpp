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

    page = root()->addNew<Wt::WContainerWidget>();
    
    navbar = page->addNew<NavbarWidget>();
    body = page->addNew<Wt::WText>("Home Page");
}

Application::~Application()
{
    
}

void Application::handleInternalPath(const std::string &internalPath)
{
    if (internalPath == "/home")
    {
        page->removeWidget(body);
        body = page->addNew<Wt::WText>("Temp Home Page");
    }
    else if (internalPath == "/menu")
    {
        page->removeWidget(body);
        body = page->addNew<MenuPage>();
    }
    else if (internalPath == "/orders")
    {
        page->removeWidget(body);
        body = page->addNew<OrderListPage>();
    }
    else if (internalPath == "/inventory")
    {
        page->removeWidget(body);
        body = page->addNew<Wt::WText>("Temp Inventory Page");
    }
    else if (internalPath == "/cart")
    {
        page->removeWidget(body);
        body = page->addNew<Wt::WText>("Temp Cart Page");
    }
    else if (internalPath == "/login")
    {
        page->removeWidget(body);
        body = page->addNew<Wt::WText>("Temp Login Page");
    }
    else
    {
        setInternalPath("/home", true);
    }
}
