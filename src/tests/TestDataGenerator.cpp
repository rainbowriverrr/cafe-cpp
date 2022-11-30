//
//  TestDataGenerator.cpp
//
//  Created by Julian Koksal on 2022-11-16.
//

#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iostream>

#include "Authenticator.hpp"
#include "DBHelper.hpp"
#include "MenuItem.hpp"
#include "OrderMaster.hpp"
#include "OrderDetail.hpp"

std::string formatDateTime(std::tm time)
{
    mktime(&time);
    char time_str[20];
    std::strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", &time);
    
    return std::string(time_str);
}

/**
 * @brief Prints a progress bar.
 *
 * @param progress the progress from 0 to 1
 */
void printProgress(double progress)
{
    std::cout << "[";
    int endOfArrowPos = progress * 50;
    for (int i = 0; i < 50; ++i)
    {
        if (i < endOfArrowPos)
        {
            std::cout << "=";
        }
        else if (i > endOfArrowPos)
        {
            std::cout << " ";
        }
        else
        {
            std::cout << ">";
        }
    }
    std::cout << "] " << (int)(progress * 100) << " %\r" << std::flush;
}

/**
 * @brief Generates some predefined menu items.
 *
 * @return a vector of the menu items that were generated
 */
std::vector<MenuItem> generateMenuItems()
{
    std::cout << "Generating menu items..." << std::endl;
    
    const DBHelper &db = DBHelper::getInstance();
    
    std::vector<MenuItem> menu = {
        MenuItem("Undefined Symbol (Blonde Roast)", 2.29, "Light bodied and smooth, with notes of berry and vanilla."),
        MenuItem("Memory Leak (Medium Roast)", 2.49, "Rich and velvety. Our signature blend."),
        MenuItem("Segmentation Fault (Dark Roast)", 2.49, "Bold flavour, with notes of dark chocolate and cinnamon."),
        MenuItem("GNUppuccino", 3.49, "Smooth espresso topped with steamed milk and foam."),
        MenuItem("GNUppuccino++", 4.29, "GNUppuccino with an extra shot of espresso."),
        MenuItem("std::onut", 2.99, "Chocolate dipped donut. Made fresh every morning."),
        MenuItem("Stack Overflow", 8.99, "Cripy bacon, fried egg, and cheddar cheese stacked on a toasted English muffin."),
        MenuItem("Brunc.h Special", 16.99, "Scrambled eggs, breakfast sausage, home fries, and two pieces of toast. Made fresh when you order."),
    };
    
    for (int i = 0; i < menu.size(); ++i)
    {
        db.insert(menu[i]);
        printProgress(i / (menu.size() - 1));
    }
    
    std::cout << std::endl << "Complete!" << std::endl;
    
    return menu;
}

/**
 * @brief Generates completed orders for the past year.
 *
 * The order details are mostly random, but quantities increase over time and certain menu items are weighted more than others.
 */
void generatePastOrders(std::tm *localTm, std::mt19937 &rng, std::vector<MenuItem> &menu)
{
    std::cout << "Generating past orders..." << std::endl;
    
    const DBHelper &db = DBHelper::getInstance();
    
    std::tm time = *localTm;
    
    // Weights for menu items in the order they are inserted.
    std::vector<int> weights = { 4, 9, 7, 3, 2, 5, 4, 3 };
    
    int daysToGenerate = 367;
    for (int daysAgo = 1; daysAgo <= daysToGenerate; ++daysAgo)
    {
        time.tm_mday = time.tm_mday - 1;
        int orderNumber = (int)db.insert(OrderMaster(0, "Bob", formatDateTime(time), "complete"));
        int daysSinceStart = daysToGenerate - daysAgo + 1;
        
        std::uniform_int_distribution<int> distr(2, 5 + (daysSinceStart / 20));
        
        for (int iMenu = 0; iMenu < menu.size(); ++iMenu)
        {
            for (int i = 0; i < weights[iMenu]; ++i)
            {
                int quantity = (daysSinceStart / 20) + distr(rng);
                
                db.insert(OrderDetail(0, orderNumber, menu[iMenu].getName(), quantity));
            }
        }
        
        printProgress((double)daysAgo / 367);
    }
    
    std::cout << std::endl << "Complete!" << std::endl;
}

/**
 * @brief Generates some uncompleted orders for the current day.
 */
void generateCurrentOrders(std::tm *localTm, std::mt19937 &rng, std::vector<MenuItem> &menu)
{
    std::cout << "Generating current orders..." << std::endl;

    const DBHelper &db = DBHelper::getInstance();
    
    std::uniform_int_distribution<int> distr(0, 50);
    
    std::tm time = *localTm;
    
    OrderMaster order;
    int orderNumber;
    OrderDetail d1, d2, d3;
    
    printProgress(0);

    order = OrderMaster(0, "Dave", formatDateTime(time), "ordered");
    orderNumber = (int)db.insert(order);
    d1 = OrderDetail(0, orderNumber, "Brunc.h Special", 1);
    d2 = OrderDetail(0, orderNumber, "Segmentation Fault (Dark Roast)", 1);
    db.insert(d1);
    db.insert(d2);
    time.tm_sec = time.tm_sec - (10 + distr(rng));
    printProgress(0.25);
    
    order = OrderMaster(0, "Carol", formatDateTime(time), "ordered");
    orderNumber = (int)db.insert(order);
    d1 = OrderDetail(0, orderNumber, "GNUppuccino", 2);
    db.insert(d1);
    time.tm_sec = time.tm_sec - (10 + distr(rng));
    printProgress(0.50);
    
    order = OrderMaster(0, "Bob", formatDateTime(time), "ordered");
    orderNumber = (int)db.insert(order);
    d1 = OrderDetail(0, orderNumber, "Undefined Symbol (Blonde Roast)", 2);
    d2 = OrderDetail(0, orderNumber, "Memory Leak (Medium Roast)", 2);
    d3 = OrderDetail(0, orderNumber, "std::onut", 3);
    db.insert(d1);
    db.insert(d2);
    db.insert(d3);
    time.tm_sec = time.tm_sec - (10 + distr(rng));
    printProgress(0.75);
    
    order = OrderMaster(0, "Alice", formatDateTime(time), "ordered");
    orderNumber = (int)db.insert(order);
    d1 = OrderDetail(0, orderNumber, "Segmentation Fault (Dark Roast)", 1);
    d2 = OrderDetail(0, orderNumber, "Stack Overflow", 1);
    db.insert(d1);
    db.insert(d2);
    time.tm_sec = time.tm_sec - (10 + distr(rng));
    printProgress(1.00);

    std::cout << std::endl << "Complete!" << std::endl;
}

/**
 * @brief Generates the first admin with username "admin", password "cafec++"
 */
void generateAdmin()
{
    Authenticator().CreateNewAdmin("admin", "testing123");
}

/**
 * @brief Runs the data generation functions.
 */
int main(int argc, const char *argv[])
{
    // RNG
    std::mt19937 rng;
    rng.seed((int)time(0));
    
    // Current local datetime
    const std::time_t currentTime = time(0);
    std::tm *localTm = std::localtime(&currentTime);
    
    // Test data generation
    
    std::vector<MenuItem> menu = generateMenuItems();
    
    generatePastOrders(localTm, rng, menu);
    
    generateCurrentOrders(localTm, rng, menu);
    
    generateAdmin();
}
