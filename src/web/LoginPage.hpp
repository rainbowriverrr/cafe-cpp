/*
    Author : Alex Mihas
    Date   : 2022/11/20
*/

#ifndef LoginPage_h
#define LoginPage_h

#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WPanel.h>
#include <Wt/WTable.h>
#include <Wt/WPushButton.h>
#include <Wt/WLink.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WFlags.h>
#include <Wt/WAnimation.h>

#include <ctime>
#include <string>

#include "DBHelper.hpp"
#include "MenuItem.hpp"
#include "MenuWidgets.hpp"
#include "OrderDetail.hpp"
#include "OrderMaster.hpp"

class LoginPage : public Wt::WContainerWidget {
   public:
    /**
     * @brief Construct a new Login Page object
     *
     */
    LoginPage();

    /**
     * @brief Destroy the Login Page object
     *
     */
    ~LoginPage();
};

#endif /* LoginPage_h */
