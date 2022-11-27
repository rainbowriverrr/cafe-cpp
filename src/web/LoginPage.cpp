/*
    Author : Alex Mihas
    Date   : 2022/11/20
*/

#include "LoginPage.hpp"
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WRadioButton.h>

LoginPage::LoginPage() {
    
    
    auto text
      = addNew<Wt::WText>("<p>Please enter your username and password.</p>");
    
    
    auto result = addNew<Wt::WTemplate>(Wt::WString::tr("simpleForm-template"));
    
    
    auto username = result->bindWidget("user-name", std::make_unique<Wt::WLineEdit>());
    username->setPlaceholderText("username");
    
    auto password = result->bindWidget("user-password", std::make_unique<Wt::WLineEdit>());
    password->setPlaceholderText("password");
    
    auto button = result->bindWidget("button", std::make_unique<Wt::WPushButton>("Log In"));
    
    auto out = result->bindWidget("out", std::make_unique<Wt::WText>());
    

    
    

    button->clicked().connect([=] {
        out->setText("Your username is " + username->text() + ". Your password is " + password->text());
        
        // authenticate
    });
}

LoginPage::~LoginPage() {
}
