//
//  main.cpp
//  DAL Test
//
//  Created by Julian Koksal on 2022-09-25.
//

#include <iostream>
#include <iomanip>
#include <string>
#include "DBHelper.hpp"
#include "MenuItem.hpp"

void printMenu(std::vector<MenuItem> &menu, std::string header)
{
    std::cout << header << std::endl;
    for (int i = 0; i < menu.size(); i++)
    {
        std::cout << "  ";
        std::cout << std::left  << std::setw(18) << menu[i].getName() << "$";
        std::cout << std::right << std::setw(6)  << std::fixed << std::setprecision(2) << menu[i].getPrice();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, const char * argv[])
{
    DBHelper db = DBHelper();
    db.createTableMenuItem();
    
    MenuItem m1 = MenuItem("Coffee", 2.29);
    MenuItem m2 = MenuItem("Latte", 3.00);
    MenuItem m3 = MenuItem("Cappuccino", 3.00);
    MenuItem m4 = MenuItem("Cookie", 1.49);
    MenuItem m5 = MenuItem("Lunch Combo 1", 10.99);
    MenuItem m6 = MenuItem("Lunch Combo 2", 11.99);
    MenuItem m7 = MenuItem("Breakfast Combo", 9.99);
    
    
    // --- INSERT into database ---
    
    db.insert(&m1);
    db.insert(&m2);
    db.insert(&m3);
    db.insert(&m4);
    db.insert(&m5);
    db.insert(&m6);
    db.insert(&m7);
    
    
    // --- SELECT from database ---
    
    std::vector<MenuItem> menu;
    
    // This MenuItem object will not be affected, and its values do not matter.
    // It is used only to determine the table name and to help create MenuItem objects from the database table rows.
    MenuItem menuItemModel = MenuItem();
    
    
    menu = db.selectWhere(&menuItemModel);
    
    printMenu(menu, "Full Menu, unsorted:");
    
    
    // These may be in a different order than the query above, even though both are unsorted.
    // If orderBy is not specified, then order does not matter! It will be given in any order that SQLite3 decides.
    menu = db.selectWhere(&menuItemModel, { }, "", { "name" });
    
    printMenu(menu, "Full Menu, unsorted, only name selected:");

    
    menu = db.selectWhere(&menuItemModel, { }, "price");
    
    printMenu(menu, "Full Menu, sorted by ascending price:");
    
    
    menu = db.selectWhere(&menuItemModel, { }, "price,name");
    
    printMenu(menu, "Full Menu, sorted by ascending price, then name:");
    
    
    menu = db.selectWhere(&menuItemModel, { SqlCondition("price", ">=", 3.00), SqlCondition("price", "<", 10.00) }, "price DESC");
    
    printMenu(menu, "Menu where 3.00 <= price < 10.00, sorted by descending price:");
    
    
    menu = db.selectWhere(&menuItemModel, { SqlCondition("name", "=", "Cookie") });
    
    printMenu(menu, "Menu where name = 'cookie', unsorted:");
    
    
    menu = db.selectWhere(&menuItemModel, { SqlCondition("name", "startswith", "co") });
    
    printMenu(menu, "Menu where name starts with 'co', unsorted:");
    
    
    menu = db.selectWhere(&menuItemModel, { SqlCondition("name", "contains", "combo") }, "price");
    
    printMenu(menu, "Menu where name contains 'combo', sorted by ascending price.");
    
    
    // --- UPDATE database ---
    
    m6.setPrice(69.99);
    db.update(&m6);
    menu = db.selectWhere(&menuItemModel);
    
    printMenu(menu, "Full menu after Lunch Combo 2 price was updated to 69.99, unsorted:");
    
    
    MenuItem updatedModel = MenuItem("", 29.99);
    db.updateWhere(&updatedModel, { SqlCondition("price", ">", 9.99) }, { "price" });
    menu = db.selectWhere(&menuItemModel);

    printMenu(menu, "Full menu after price was updated to 29.99 where price > 9.99, unsorted:");
    
    
    // --- DELETE from database ---
    
    db.destroy(&m6);
    menu = db.selectWhere(&menuItemModel);

    printMenu(menu, "Full menu after Lunch Combo 2 was deleted, unsorted:");
    
    
    db.destroyWhere(&menuItemModel, { SqlCondition("price", "<=", 5.00) });
    menu = db.selectWhere(&menuItemModel);
    
    printMenu(menu, "Full menu after everything with price <= 5.00 was deleted, unsorted:");
    
    
    db.destroyWhere(&menuItemModel, { });
    menu = db.selectWhere(&menuItemModel);

    printMenu(menu, "Full menu after everything was deleted:");
    
    return 0;
}
