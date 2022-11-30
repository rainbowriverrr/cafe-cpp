/*
    Author : River Wang
    Date   : 2022/10/31
*/

#include "Application.hpp"

Application::Application(const Wt::WEnvironment &env) : Wt::WApplication(env)
{
    setTitle("Cafe C++");
    
    setLoadingIndicator(std::make_unique<CustomLoadingIndicator>());

    useStyleSheet("resources/css/style.css");
    messageResourceBundle().use("resources/html/templates");

    internalPathChanged().connect(this, &Application::handleInternalPath);
    
    auth = new Authenticator();
    
    navbar = root()->addNew<NavbarWidget>();
    body = root()->addNew<HomePage>();
    
    setInternalPath("/home", false);
}

Application::~Application()
{
    delete auth;
}

void Application::handleInternalPath(const std::string &internalPath)
{
    root()->removeWidget(body);
    
    if (internalPath == "/home")
    {
        body = root()->addNew<HomePage>();
    }
    else if (internalPath == "/menu")
    {
        body = root()->addNew<MenuPage>();
    }
    else if (internalPath == "/orders")
    {
        body = root()->addNew<OrderListPage>();
    }
    else if (internalPath == "/sales")
    {
        body = root()->addNew<SalesPage>();
    }
//    else if (internalPath == "/inventory")
//    {
//        body = root()->addNew<InventoryPage>();
//    }
    else if (internalPath == "/cart")
    {
        body = root()->addNew<CartPage>();
    }
    else if (internalPath == "/create-user")
    {
        body = root()->addNew<CreateAdminPage>();
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

Authenticator * Application::getAuth()
{
    return auth;
}

void Application::reset()
{
    root()->removeWidget(navbar);
    root()->removeWidget(body);
    
    navbar = root()->addNew<NavbarWidget>();
    body = root()->addNew<HomePage>();
    
    setInternalPath("/home", false);
}
