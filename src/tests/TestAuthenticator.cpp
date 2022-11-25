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

    Admin a1 = Admin("Sharon", "Nikritin");
    Admin a2 = Admin("Julian", "Koksal");
    Admin a3 = Admin("River", "Wang");
    Admin a4 = Admin("Alex", "Mias");
    Admin a5 = Admin("Daniel", "McGar");


    db.insert(a1);
    db.insert(a2);
    db.insert(a3);
    db.insert(a4);
    db.insert(a5);

    Authenticator auth;
    auth.CreateNewAdmin("Sharon", "Nikritin");

}