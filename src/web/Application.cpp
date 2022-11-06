/*
    Author : River Wang
    Date   : 2022/10/31
*/

#include "Application.hpp"

Application::Application(const Wt::WEnvironment &env)
    : Wt::WApplication(env) {
    setTitle("Hello world");

    // root()->addWidget(std::make_unique<Wt::WText>("Your name, please ? "));
    // nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    // auto button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
    // root()->addWidget(std::make_unique<Wt::WBreak>());
    // greeting_ = root()->addWidget(std::make_unique<Wt::WText>());
    // auto greet = [this] {
    //     greeting_->setText("Hello there, " + nameEdit_->text());
    // };
    // button->clicked().connect(greet);

    MenuItem *item1 = root()->addWidget(std::make_unique<MenuItem>("item1", "1.00", "item1 description", nullptr));
}

int main(int argc, char **argv) {
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
        return std::make_unique<Application>(env);
    });
}