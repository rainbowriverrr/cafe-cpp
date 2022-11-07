/*
    Author : River Wang
    Date   : 2022/10/31
*/

#include "Application.hpp"

#include "MenuItem.hpp"

void renderMenu(Wt::WContainerWidget *root, DBHelper *dbHelper) {
    MenuItem itemModel = MenuItem();

    root->addWidget(std::make_unique<MenuItemWidget>("Name", "Price", "Description", nullptr));

    std::vector<MenuItem> menuItems = dbHelper->selectWhere(&itemModel);
    for (int i = 0; i < menuItems.size(); i++) {
        root->addWidget(std::make_unique<MenuItemWidget>(menuItems[i].getName(), std::to_string(menuItems[i].getPrice()), "description here", nullptr));
    }
}

Application::Application(const Wt::WEnvironment &env, DBHelper *dbHelper)
    : Wt::WApplication(env) {
    db = dbHelper;
    setTitle("Hello world");

    messageResourceBundle().use(appRoot() + "templates");

    renderMenu(root(), dbHelper);
}

int main(int argc, char **argv) {
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
        DBHelper *db = new DBHelper();

        // DB Test
        // MenuItem m1 = MenuItem("Coffee", 2.29);
        // MenuItem m2 = MenuItem("Latte", 3.00);
        // MenuItem m3 = MenuItem("Cappuccino", 3.00);
        // MenuItem m4 = MenuItem("Cookie", 1.49);
        // MenuItem m5 = MenuItem("Lunch Combo 1", 10.99);
        // MenuItem m6 = MenuItem("Lunch Combo 2", 11.99);
        // MenuItem m7 = MenuItem("Breakfast Combo", 9.99);

        // // --- INSERT into database ---

        // db->insert(&m1);
        // db->insert(&m2);
        // db->insert(&m3);
        // db->insert(&m4);
        // db->insert(&m5);
        // db->insert(&m6);
        // db->insert(&m7);

        return std::make_unique<Application>(env, db);
    });
}