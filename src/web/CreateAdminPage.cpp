//
//  CreateAdminPage.cpp
//

#include "CreateAdminPage.hpp"

CreateAdminPage::CreateAdminPage() {
    addStyleClass("list");
    
    auto pageElements = addNew<Wt::WTemplate>(Wt::WString::tr("login-template"));
    
    auto usernameField = pageElements->bindWidget("user-name", std::make_unique<Wt::WLineEdit>());
    usernameField->setPlaceholderText("Username");
    
    auto passwordField = pageElements->bindWidget("user-password", std::make_unique<Wt::WLineEdit>());
    passwordField->setPlaceholderText("Password");
    passwordField->setEchoMode(Wt::EchoMode::Password);
    
    auto logInButton = pageElements->bindWidget("login-button", std::make_unique<Wt::WPushButton>("Create Account"));
    
    auto outputWhenButtonClicked = pageElements->bindWidget("out", std::make_unique<Wt::WText>());

    // this is the method that occurs when the "Log-In" button is pressed
    logInButton->clicked().connect([this, usernameField, passwordField, outputWhenButtonClicked] {
        Authenticator *authenticatorObject = ((Application *)Application::instance())->getAuth();
        
        // attempt to create admin with the credentials the user provided
        bool result = authenticatorObject->CreateNewAdmin(usernameField->text().toUTF8(), passwordField->text().toUTF8());
        
        // check if successful
        if (result) {
            outputWhenButtonClicked->setText("Account created.");
            usernameField->setText("");
            passwordField->setText("");
        }
        else if (passwordField->text().toUTF8().length() < 9) {
            outputWhenButtonClicked->setText("Error: Password must be at least 9 characters.");
        }
        else {
            outputWhenButtonClicked->setText("Error: An account with that username already exists.");
        }
    });
}

CreateAdminPage::~CreateAdminPage() {
}
