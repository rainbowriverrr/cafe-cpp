/*
    Author : Alex Mihas
    Date   : 2022/11/20
*/

#include "LoginPage.hpp"

LoginPage::LoginPage() {
    Wt::WContainerWidget *listWidget;
    
    listWidget = addNew<WContainerWidget>();
    
    listWidget->addNew<Wt::WTemplate>(tr("login-page"));
    
    
    //Wt::WApplication::instance()->setInternalPath("/login", true);
}

LoginPage::~LoginPage() {
}
