/*
    Author : River Wang
    Date   : 2022/10/31
*/

#include "Application.hpp"

Application::Application(const Wt::WEnvironment &env): Wt::WApplication(env)
{
    setTitle("Cafe C++");
    
    internalPathChanged().connect(this, &Application::handleInternalPath);
    
    useStyleSheet("resources/style.css");
    
    page = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    
    navbar = page->addWidget(std::make_unique<Wt::WTemplate>(readHtml("navbar.html")));
    
    Wt::WLink linkHome = Wt::WLink(Wt::LinkType::InternalPath, "/home");
    navbar->bindWidget("a-home", std::make_unique<Wt::WAnchor>(linkHome, std::make_unique<Wt::WImage>("resources/cpp_logo.png")));
    
    Wt::WLink linkMenu = Wt::WLink(Wt::LinkType::InternalPath, "/menu");
    navbar->bindWidget("a-menu", std::make_unique<Wt::WAnchor>(linkMenu, "menu"));
    
    Wt::WLink linkOrders = Wt::WLink(Wt::LinkType::InternalPath, "/orders");
    navbar->bindWidget("a-orders", std::make_unique<Wt::WAnchor>(linkOrders, "orders"));
    
    stack = page->addWidget(std::make_unique<Wt::WStackedWidget>());
    
    pageHome = stack->addWidget(std::make_unique<Wt::WText>("Home Page"));
    pageMenu = stack->addWidget(std::make_unique<Wt::WText>("Menu Page"));
    pageOrders = stack->addWidget(std::make_unique<Wt::WText>("Orders Page"));

//    root()->addWidget(std::make_unique<Wt::WText>("Your name, please ? "));
//    nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
//    auto button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet me."));
//    root()->addWidget(std::make_unique<Wt::WBreak>());
//    greeting_ = root()->addWidget(std::make_unique<Wt::WText>());
//    auto greet = [this] {
//        greeting_->setText("Hello there, " + nameEdit_->text());
//    };
//    button->clicked().connect(greet);
}

void Application::handleInternalPath(const std::string &internalPath)
{
    if (internalPath == "/home")
    {
        stack->setCurrentWidget(pageHome);
    }
    else if (internalPath == "/menu")
    {
        stack->setCurrentWidget(pageMenu);
    }
    else if (internalPath == "/orders")
    {
        stack->setCurrentWidget(pageOrders);
    }
    else
    {
        WApplication::instance()->setInternalPath("/home", true);
    }
}

const Wt::WString Application::readHtml(std::string fileName)
{
    std::string html = "";
    
    std::ifstream in;
    in.open("resources/" + fileName);
    if (in.is_open())
    {
        html.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    }
    in.close();
    
    return Wt::WString(html);
}
