//
// Created by Sharon Nikritin on 2022-11-24.
//

#include <iomanip>
#include <iostream>
#include <string>

#include "DBHelper.hpp"
#include "Authenticator.hpp"
#include "Admin.hpp"

int main (int argc, const char *argv[]){
    const DBHelper &db = DBHelper::getInstance();

    Authenticator auth;
    //Test with proper password
    auth.CreateNewAdmin("Sharon", "WaterBottle");
    auth.LogIn("Sharon", "WaterBottle");

    bool test = auth.IsLoggedIn();
    printf("Proper Password: %d\n", test);

    Authenticator auth1;
    //Test with to0 short password
    bool test1 = auth1.CreateNewAdmin("River", "Ocean");
    printf("Too short password: %d\n", test1);

    Authenticator auth2;
    //Test with wrong password
    auth2.CreateNewAdmin("Dimitri", "hello12345");
    auth2.LogIn("Dimitri", "hello1234");

    bool test2 = auth2.IsLoggedIn();

    printf("Wrong Password: %d\n", test2);

}