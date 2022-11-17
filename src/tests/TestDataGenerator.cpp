//
//  TestDataGenerator.cpp
//
//  Created by Julian Koksal on 2022-11-16.
//

#include <string>
#include <vector>
#include <cmath>

#include <Wt/WDateTime.h>
#include <Wt/WRandom.h>

#include "DBHelper.hpp"
#include "OrderMaster.hpp"
#include "OrderDetail.hpp"

void generateOrders()
{
    const DBHelper &db = DBHelper::getInstance();
    
    std::vector<std::string> menu = {
        "GNUppuccino", "GNUppuccino", "GNUppuccino",
        "Memory Leak", "Memory Leak", "Memory Leak", "Memory Leak", "Memory Leak", "Memory Leak", "Memory Leak", "Memory Leak", "Memory Leak",
        "Segmentation Fault", "Segmentation Fault", "Segmentation Fault", "Segmentation Fault", "Segmentation Fault", "Segmentation Fault",
        "Stack Overflow", "Stack Overflow",
        "Undefined Symbol", "Undefined Symbol", "Undefined Symbol", "Undefined Symbol"
    };
    
    int daysToGenerate = 366;
    for (int daysAgo = 1; daysAgo <= daysToGenerate; daysAgo++)
    {
        Wt::WDateTime day = Wt::WDateTime::currentDateTime().addDays(daysAgo * -1);
        int orderNumber = (int)db.insert(OrderMaster(0, "Bob", day.toString("yyyy-MM-dd HH:mm:ss.zzz").toUTF8(), 1));
        
        for (std::vector<std::string>::iterator it = menu.begin(); it != menu.end(); it++)
        {
            int daysSinceStart = daysToGenerate - daysAgo + 1;
            
            int quantity = (Wt::WRandom::get() % (30 + (daysSinceStart / 5))) + 10;
            
            db.insert(OrderDetail(0, orderNumber, *it, quantity));
        }
    }
}

int main(int argc, const char *argv[])
{
    generateOrders();
}
