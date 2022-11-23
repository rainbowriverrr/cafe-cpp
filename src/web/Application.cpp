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
    
    setInternalPath("/home", false);
}

Application::~Application()
{
    
}

void Application::handleInternalPath(const std::string &internalPath)
{
    root()->removeWidget(body);
    
    if (internalPath == "/home")
    {
        body = root()->addNew<Wt::WText>("Temp Home Page");
    }
    else if (internalPath == "/menu")
    {
        body = root()->addNew<MenuPage>();
    }
    else if (internalPath == "/orders")
    {
        body = root()->addNew<OrderListPage>();
    }
    else if (internalPath == "/inventory")
    {
        body = root()->addNew<Wt::WText>("Temp Inventory Page");
    }
    else if (internalPath == "/cart")
    {
        body = root()->addNew<Wt::WText>("Temp Cart Page");
    }
    else if (internalPath == "/login")
    {
        body = root()->addNew<LoginPage>();
    }
    else
    {
        setInternalPath("/home", true);
        return;
    }
    
    // Underlines the navbar item that was navigated to.
    doJavaScript("const items = document.getElementsByClassName('navbar-item');"
                 "for (const item of items) item.classList.remove('navbar-item-active');"
                 "document.getElementById('navbar-item-" + internalPath.substr(1) + "').classList.add('navbar-item-active');");
}
