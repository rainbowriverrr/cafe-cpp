/*
    Author : Alex Mihas
    Date   : 2022/11/20
*/

#include "LoginPage.hpp"

LoginPage::LoginPage() {
    
    Authenticator authenticatorObject = Authenticator();
    
    auto instructionsText
      = addNew<Wt::WText>("<p>Please enter your username and password.</p>");
    
    auto pageElements = addNew<Wt::WTemplate>(Wt::WString::tr("login-template"));
    
    auto usernameField = pageElements->bindWidget("user-name", std::make_unique<Wt::WLineEdit>());
    usernameField->setPlaceholderText("Username");
    
    auto passwordField = pageElements->bindWidget("user-password", std::make_unique<Wt::WLineEdit>());
    passwordField->setPlaceholderText("Password");
    
    auto logInButton = pageElements->bindWidget("login-button", std::make_unique<Wt::WPushButton>("Log In"));
    
    auto outputWhenButtonClicked = pageElements->bindWidget("out", std::make_unique<Wt::WText>());

    // this is the method that occurs when the "Log-In" button is pressed
    logInButton->clicked().connect([=] {
        // attempt to log-in with the credentials the user provided
        authenticatorObject.LogIn(usernameField->text(), passwordField)
        
        // check if we are logged in
        if (authenticatorObject.isLoggedIn()) {
            outputWhenButtonClicked->setText("You have successfully logged in.");
        }
        else {
            outputWhenButtonClicked->setText("Error: Incorrect username and/or password");
        }
        
  
    });
}

LoginPage::~LoginPage() {
}
