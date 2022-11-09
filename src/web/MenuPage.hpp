/*
    Author : River Wang
    Date   : 2022/11/08
*/

#ifndef MenuPage_hpp
#define MenuPage_hpp

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>

#include <string>

#include "DBHelper.hpp"
#include "MenuItem.hpp"
#include "MenuWidgets.hpp"
#include "OrderDetail.h"
#include "OrderMaster.hpp"

class MenuPage : public Wt::WContainerWidget {
   public:
    /**
     * @brief Construct a new Menu Page object
     *
     */
    MenuPage(Wt::WApplication *instance);

    /**
     * @brief Destroy the Menu Page object
     *
     */
    ~MenuPage();

    /**
     * @brief Orders menu item and redirects to orders page
     *
     */
    void orderMenuItem(MenuItem);
};

#endif