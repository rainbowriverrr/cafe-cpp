//
//  NavbarWidget.cpp
//
//  Created by Julian Koksal on 2022-11-07.
//

#include "NavbarWidget.hpp"

NavbarWidget::NavbarWidget()
{
    Wt::WTemplate *navbarTemplate = addNew<Wt::WTemplate>(IOHelper::readHtml("w_navbar.html"));
    
    Wt::WLink linkHome = Wt::WLink(Wt::LinkType::InternalPath, "/home");
    navbarTemplate->bindWidget("a-home", std::make_unique<Wt::WAnchor>(linkHome, std::make_unique<Wt::WImage>("resources/images/logo.png")));
    
    Wt::WLink linkMenu = Wt::WLink(Wt::LinkType::InternalPath, "/menu");
    navbarTemplate->bindWidget("a-menu", std::make_unique<Wt::WAnchor>(linkMenu, "menu"));
    
    Wt::WLink linkOrders = Wt::WLink(Wt::LinkType::InternalPath, "/orders");
    navbarTemplate->bindWidget("a-orders", std::make_unique<Wt::WAnchor>(linkOrders, "orders"));
}

NavbarWidget::~NavbarWidget()
{
    
}
