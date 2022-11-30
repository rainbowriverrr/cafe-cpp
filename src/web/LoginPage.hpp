/*
    Author : Alex Mihas
    Date   : 2022/11/20
*/

#ifndef LoginPage_h
#define LoginPage_h

#include <Wt/WTemplate.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

#include <ctime>
#include <string>

#include "Application.hpp"
#include "Authenticator.hpp"
#include "Page.hpp"

class LoginPage : public Page {
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
