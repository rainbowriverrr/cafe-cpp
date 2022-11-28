//
// Created by Sharon Nikritin on 2022-11-17.
//

#ifndef Authenticator_hpp
#define Authenticator_hpp

#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>


#include "DBhelper.hpp"
#include "Admin.hpp"

class Authenticator {
public:

    Authenticator();

    ~Authenticator();

    bool IsLoggedIn ();

    bool CreateNewAdmin (std:: string username, std::string password);

    void LogOut();

    void LogIn(std::string username, std::string password);

private:
    int minChars;
    bool isLoggedIn;
    bool CheckCredentials (std::string username, std::string password);
    const DBHelper &db = DBHelper::getInstance();
    std::hash<std::string> hasher;
    std::vector<Admin> admin;


};


#endif //Authenicator.hpp
