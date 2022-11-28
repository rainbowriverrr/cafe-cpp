//
//  NavbarWidget.cpp
//
//  Created by Julian Koksal on 2022-11-07.
//

#include "NavbarWidget.hpp"

NavbarWidget::NavbarWidget()
{
    addStyleClass("sticky-top");
    
    bool isLoggedIn = ((Application *)Application::instance())->getAuth()->IsLoggedIn();
    if (isLoggedIn)
    {
        addWidget(createAdminNavbarWidget());
    }
    else
    {
        addWidget(createCustomerNavbarWidget());
    }
}

NavbarWidget::~NavbarWidget()
{
    
}

std::unique_ptr<Wt::WTemplate> NavbarWidget::createCustomerNavbarWidget()
{
    std::unique_ptr<Wt::WTemplate> navTemplate = std::make_unique<Wt::WTemplate>(tr("navbar-customer"));
    
    bindCommonNavbarAnchors(navTemplate.get());
    
    Wt::WLink linkCart = Wt::WLink(Wt::LinkType::InternalPath, "/cart");
    navTemplate->bindWidget("a-cart", std::make_unique<Wt::WAnchor>(linkCart, std::make_unique<Wt::WImage>("resources/images/cart.png")));
    
    Wt::WLink linkLogin = Wt::WLink(Wt::LinkType::InternalPath, "/login");
    Wt::WAnchor *loginAnchor = navTemplate->bindWidget("a-login", std::make_unique<Wt::WAnchor>(linkLogin, "login"));
    // DEBUG. TO BE REPLACED BY LOGIN PAGE.
    loginAnchor->clicked().connect([] {
        ((Application *)Application::instance())->getAuth()->LogIn("admin", "cafec++12345");
    });
    
    return navTemplate;
}

std::unique_ptr<Wt::WTemplate> NavbarWidget::createAdminNavbarWidget()
{
    std::unique_ptr<Wt::WTemplate> navTemplate = std::make_unique<Wt::WTemplate>(tr("navbar-admin"));
    
    bindCommonNavbarAnchors(navTemplate.get());
    
    Wt::WLink linkSales = Wt::WLink(Wt::LinkType::InternalPath, "/sales");
    navTemplate->bindWidget("a-sales", std::make_unique<Wt::WAnchor>(linkSales, "sales"));
    
    Wt::WLink linkInventory = Wt::WLink(Wt::LinkType::InternalPath, "/inventory");
    navTemplate->bindWidget("a-inventory", std::make_unique<Wt::WAnchor>(linkInventory, "inventory"));
    
    Wt::WLink linkCreateUser = Wt::WLink(Wt::LinkType::InternalPath, "/create-user");
    navTemplate->bindWidget("a-create-user", std::make_unique<Wt::WAnchor>(linkCreateUser, "create user"));
    
    Wt::WLink linkHome = Wt::WLink(Wt::LinkType::InternalPath, "/home");
    Wt::WAnchor *logoutAnchor = navTemplate->bindWidget("a-logout", std::make_unique<Wt::WAnchor>(linkHome, "logout"));
    logoutAnchor->clicked().connect([] {
        ((Application *)Application::instance())->getAuth()->LogOut();
    });
    
    return navTemplate;
}

void NavbarWidget::bindCommonNavbarAnchors(Wt::WTemplate *navTemplate)
{
    Wt::WLink linkHome = Wt::WLink(Wt::LinkType::InternalPath, "/home");
    navTemplate->bindWidget("a-home", std::make_unique<Wt::WAnchor>(linkHome, std::make_unique<Wt::WImage>("resources/images/logo.png")));
    
    Wt::WLink linkMenu = Wt::WLink(Wt::LinkType::InternalPath, "/menu");
    navTemplate->bindWidget("a-menu", std::make_unique<Wt::WAnchor>(linkMenu, "menu"));
    
    Wt::WLink linkOrders = Wt::WLink(Wt::LinkType::InternalPath, "/orders");
    navTemplate->bindWidget("a-orders", std::make_unique<Wt::WAnchor>(linkOrders, "orders"));
}
