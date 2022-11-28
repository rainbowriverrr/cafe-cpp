/*
    Author : Alex Mihas
    Date   : 2022/11/20
*/

#include "LoginPage.hpp"

LoginPage::LoginPage() {
    
    
    auto instructionsText
      = addNew<Wt::WText>("<p>Please enter your username and password.</p>");
    
    auto pageElements = addNew<Wt::WTemplate>(Wt::WString::tr("login-template"));
    
    auto usernameField = pageElements->bindWidget("user-name", std::make_unique<Wt::WLineEdit>());
    usernameField->setPlaceholderText("Enter username");
    
    auto passwordField = pageElements->bindWidget("user-password", std::make_unique<Wt::WLineEdit>());
    passwordField->setPlaceholderText("Enter password");
    
    auto logInButton = pageElements->bindWidget("login-button", std::make_unique<Wt::WPushButton>("Log In"));
    
    auto outputWhenButtonClicked = pageElements->bindWidget("out", std::make_unique<Wt::WText>());

    logInButton->clicked().connect([=] {
        outputWhenButtonClicked->setText("Your username is " + usernameField->text() + ". Your password is " + passwordField->text());
        
        // authenticate method goes here
        // the username is usernameField->text()
        // the password is passwordField->text()
    });
}

LoginPage::~LoginPage() {
}
