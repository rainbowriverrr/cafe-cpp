//
//  OrderListPage.cpp
//
//  Created by Julian Koksal on 2022-11-07.
//

#include "OrderListPage.hpp"

OrderListPage::OrderListPage()
{
    std::vector<OrderMaster> orders = DBHelper::getInstance().selectWhere(OrderMaster(), { SqlCondition("isComplete", "=", 0) }, "OrderDate DESC");

    Wt::WTemplate *pageTemplate = addWidget(std::make_unique<Wt::WTemplate>(IOHelper::readHtml("page_orderList.html")));
    Wt::WContainerWidget *orderList = pageTemplate->bindWidget("w-order-list", std::make_unique<Wt::WContainerWidget>());

    for (std::vector<OrderMaster>::iterator it = orders.begin(); it != orders.end(); it++)
    {
        Wt::WTemplate *item = orderList->addWidget(std::make_unique<Wt::WTemplate>(IOHelper::readHtml("w_OrderListItem.html")));
        item->bindWidget("txt-ordernum", std::make_unique<Wt::WText>((std::to_string(it->getOrderNumber()))));
        item->bindWidget("txt-orderedby", std::make_unique<Wt::WText>(it->getOrderedBy()));
        item->bindWidget("txt-orderdate", std::make_unique<Wt::WText>(it->getOrderDate().substr(0, 19)));

        Wt::WPanel *panelOrderDetails = item->bindWidget("panel-orderdetails", std::make_unique<Wt::WPanel>());
        panelOrderDetails->setTitle(Wt::WString("View Items"));
        panelOrderDetails->setCollapsible(true);
        panelOrderDetails->collapse();
        Wt::WAnimation animation(Wt::AnimationEffect::SlideInFromTop,
                                 Wt::TimingFunction::EaseOut,
                                 100);
        panelOrderDetails->setAnimation(animation);
        panelOrderDetails->setCentralWidget(std::make_unique<Wt::WText>("Coffee"));
        panelOrderDetails->expanded().connect([this, panelOrderDetails] { panelOrderDetailsExpanded(panelOrderDetails); });
        panelOrderDetails->collapsed().connect([this, panelOrderDetails] { panelOrderDetailsCollapsed(panelOrderDetails); });
    }
}

OrderListPage::~OrderListPage()
{
    
}

void OrderListPage::panelOrderDetailsExpanded(Wt::WPanel *panel)
{
    panel->setTitle("Hide Items");
    panel->addStyleClass("expanded");
}

void OrderListPage::panelOrderDetailsCollapsed(Wt::WPanel *panel)
{
    panel->setTitle("View Items");
    panel->removeStyleClass("expanded");
}
