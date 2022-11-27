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
    
    auto container = std::make_unique<Wt::WContainerWidget>();
    Wt::WContainerWidget *listWidget;
    
    
    
    container->addNew<Wt::WRadioButton>("Radio me!");
    auto result =
        std::make_unique<Wt::WTemplate>(Wt::WString::tr("simpleForm-template"));

    auto name = result->bindWidget("name", std::make_unique<Wt::WLineEdit>());
    name->setPlaceholderText("first name");

    auto button = result->bindWidget("button", std::make_unique<Wt::WPushButton>("OK"));

    auto out = result->bindWidget("out", std::make_unique<Wt::WText>());

    button->clicked().connect([=] {
        out->setText("Hello, " + name->text() + "! I just want to help you... You"
                     + " could complete this simple form by adding validation.");
    });
}

LoginPage::~LoginPage() {
}
