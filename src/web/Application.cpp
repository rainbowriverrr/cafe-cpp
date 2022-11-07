/*
    Author : River Wang
    Date   : 2022/10/31
*/

#include "Application.hpp"

Application::Application(const Wt::WEnvironment &env): Wt::WApplication(env)
{
    db = DBHelper();
    
    setTitle("Cafe C++");
    
    internalPathChanged().connect(this, &Application::handleInternalPath);
    
    useStyleSheet("resources/style.css");
    
    page = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    
    navbar = page->addWidget(std::make_unique<Wt::WTemplate>(readHtml("w_navbar.html")));
    
    Wt::WLink linkHome = Wt::WLink(Wt::LinkType::InternalPath, "/home");
    navbar->bindWidget("a-home", std::make_unique<Wt::WAnchor>(linkHome, std::make_unique<Wt::WImage>("resources/logo.png")));
    
    Wt::WLink linkMenu = Wt::WLink(Wt::LinkType::InternalPath, "/menu");
    navbar->bindWidget("a-menu", std::make_unique<Wt::WAnchor>(linkMenu, "menu"));
    
    Wt::WLink linkOrders = Wt::WLink(Wt::LinkType::InternalPath, "/orders");
    navbar->bindWidget("a-orders", std::make_unique<Wt::WAnchor>(linkOrders, "orders"));
    
    stack = page->addWidget(std::make_unique<Wt::WStackedWidget>());
    
    pageHome = stack->addWidget(std::make_unique<Wt::WText>("Home Page"));
    pageMenu = stack->addWidget(std::make_unique<Wt::WText>("Menu Page"));
    
    // Orders Pagee
    OrderMaster orderModel = OrderMaster();
    std::vector<OrderMaster> orders = db.selectWhere(&orderModel);

    pageOrders = stack->addWidget(std::make_unique<Wt::WTemplate>(readHtml("page_orders.html")));
    Wt::WContainerWidget *orderList = pageOrders->bindWidget("w-order-list", std::make_unique<Wt::WContainerWidget>());

    for (std::vector<OrderMaster>::iterator it = orders.begin(); it != orders.end(); it++)
    {
        Wt::WTemplate *item = orderList->addWidget(std::make_unique<Wt::WTemplate>(readHtml("w_orderlistitem.html")));
        item->bindWidget("txt-ordernum", std::make_unique<Wt::WText>((std::to_string(it->getOrderNumber()))));
        item->bindWidget("txt-orderedby", std::make_unique<Wt::WText>(it->getOrderedBy()));
        item->bindWidget("txt-orderdate", std::make_unique<Wt::WText>(it->getOrderDate()));

        Wt::WPanel *panelOrderDetails = item->bindWidget("panel-orderdetails", std::make_unique<Wt::WPanel>());
        panelOrderDetails->setTitle(Wt::WString("View Details"));
        panelOrderDetails->setCollapsible(true);
        panelOrderDetails->collapse();
        Wt::WAnimation animation(Wt::AnimationEffect::SlideInFromTop,
                                 Wt::TimingFunction::EaseOut,
                                 100);
        panelOrderDetails->setAnimation(animation);
        panelOrderDetails->setCentralWidget(std::make_unique<Wt::WText>("Coffee"));
    }
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
