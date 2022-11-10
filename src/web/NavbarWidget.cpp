//
//  NavbarWidget.cpp
//
//  Created by Julian Koksal on 2022-11-07.
//

#include "NavbarWidget.hpp"

NavbarWidget::NavbarWidget()
{
    addStyleClass("sticky-top");
    
    Wt::WTemplate *navbarTemplate = addNew<Wt::WTemplate>(tr("navbar"));
    
    Wt::WLink linkHome = Wt::WLink(Wt::LinkType::InternalPath, "/home");
    navbarTemplate->bindWidget("a-home", std::make_unique<Wt::WAnchor>(linkHome, std::make_unique<Wt::WImage>("resources/images/logo.png")));
    
    Wt::WLink linkMenu = Wt::WLink(Wt::LinkType::InternalPath, "/menu");
    navbarTemplate->bindWidget("a-menu", std::make_unique<Wt::WAnchor>(linkMenu, "menu"));
    
    Wt::WLink linkOrders = Wt::WLink(Wt::LinkType::InternalPath, "/orders");
    navbarTemplate->bindWidget("a-orders", std::make_unique<Wt::WAnchor>(linkOrders, "orders"));
    
    Wt::WLink linkInventory = Wt::WLink(Wt::LinkType::InternalPath, "/inventory");
    navbarTemplate->bindWidget("a-inventory", std::make_unique<Wt::WAnchor>(linkInventory, "inventory"));
    
    Wt::WLink linkCart = Wt::WLink(Wt::LinkType::InternalPath, "/cart");
    navbarTemplate->bindWidget("a-cart", std::make_unique<Wt::WAnchor>(linkCart, std::make_unique<Wt::WImage>("resources/images/cart.png")));
    
    Wt::WLink linkLogin = Wt::WLink(Wt::LinkType::InternalPath, "/login");
    navbarTemplate->bindWidget("a-login", std::make_unique<Wt::WAnchor>(linkLogin, "login"));
}

NavbarWidget::~NavbarWidget()
{
    
}
