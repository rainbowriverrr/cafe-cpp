/*
    Author : River Wang
    Date   : 2022/10/31
*/

#include "Application.hpp"

Application::Application(const Wt::WEnvironment &env): Wt::WApplication(env)
{
    const DBHelper &db = DBHelper::getInstance();
    
    setTitle("Cafe C++");
    
    useStyleSheet("resources/style.css");
    
    internalPathChanged().connect(this, &Application::handleInternalPath);
    
    page = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    
    navbar = page->addWidget(std::make_unique<NavbarWidget>());
    
    stack = page->addWidget(std::make_unique<Wt::WStackedWidget>());

    pageHome = stack->addWidget(std::make_unique<Wt::WText>("Home Page"));
    pageMenu = stack->addWidget(std::make_unique<Wt::WText>("Menu Page"));
    pageOrderList = stack->addWidget(std::make_unique<OrderListPage>());
}

Application::~Application()
{
    
}

void Application::handleInternalPath(const std::string &internalPath)
{
    if (internalPath == "/home") {
        stack->setCurrentWidget(pageHome);
    } else if (internalPath == "/menu") {
        stack->setCurrentWidget(pageMenu);
    } else if (internalPath == "/orders") {
        stack->setCurrentWidget(pageOrderList);
    } else {
        WApplication::instance()->setInternalPath("/home", true);
    }
}

void Application::handleMenuPage()
{
    std::vector<MenuItem> menuItems = DBHelper::getInstance().selectWhere(MenuItem());
    for (int i = 0; i < menuItems.size(); i++) {
        stack->addWidget(std::make_unique<MenuItemWidget>(menuItems[i].getName(), std::to_string(menuItems[i].getPrice()), "description here", nullptr));
    }
}
