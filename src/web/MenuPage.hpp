/*
    Author : River Wang
    Date   : 2022/11/08
*/

#ifndef MenuPage_hpp
#define MenuPage_hpp

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>

#include <ctime>
#include <string>

#include "DBHelper.hpp"
#include "MenuItem.hpp"
#include "MenuWidgets.hpp"
#include "OrderDetail.hpp"
#include "OrderMaster.hpp"

class MenuPage : public Wt::WContainerWidget {
   public:
    /**
     * @brief Construct a new Menu Page object
     *
     */
    MenuPage();

    /**
     * @brief Destroy the Menu Page object
     *
     */
    ~MenuPage();
};

#endif
