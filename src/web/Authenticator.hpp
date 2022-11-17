//
// Created by Sharon Nikritin on 2022-11-17.
//

#ifndef Authenticator_hpp
#define Authenticator_hpp

#include "DBhelper.hpp"

class Authenticator {
public:

    Authenticator();

    ~Authenticator();

    bool IsLoggedIn ();

    void CreateNewAdmin (std:: string username, std::string password);

    void LogOut();

    void LogIn(std::string username, std::string password);

private:
    int minChars;
    bool isLoggedIn;
    bool CheckCredentials (std::string username, std::string password);


};


#endif //Authenicator.hpp
