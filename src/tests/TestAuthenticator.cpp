//
// Created by Sharon Nikritin on 2022-11-24.
//

#include <iostream>

#include "DBHelper.hpp"
#include "Authenticator.hpp"
#include "Admin.hpp"

int main (int argc, const char *argv[]){
    const DBHelper &db = DBHelper::getInstance();

    Admin a1 = Admin("Tree", "Christmas456");
    db.insert(a1);

    Authenticator auth;
    //Test with proper password
    auth.CreateNewAdmin("Sharon", "WaterBottle");
    auth.LogIn("Sharon", "WaterBottle");

    bool test = auth.IsLoggedIn();
    printf("Proper Password(true): %d\n", test);

    Authenticator auth1;
    //Test with to0 short password
    bool test1 = auth1.CreateNewAdmin("River", "Ocean");
    printf("Too short password(false): %d\n", test1);

    Authenticator auth2;
    //Test with wrong password
    auth2.CreateNewAdmin("Dimitri", "hello12345");
    auth2.LogIn("Dimitri", "hello1234");

    bool test2 = auth2.IsLoggedIn();

    printf("Wrong Password(false): %d\n", test2);

    //Test with different authenticator and see if the user was added to the database

    auth2.LogIn("Tree", "Christmas456");

    bool test3 = auth2.IsLoggedIn();

    printf("Different User then created in Authenticator (right password)(true): %d\n", test3);

    db.destroy(a1);

    auth.LogOut();
    bool test4 = auth.IsLoggedIn();

    printf("Log out of an user (false): %d\n", test4);
}
