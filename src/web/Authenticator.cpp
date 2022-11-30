//
// Created by Sharon Nikritin on 2022-11-17.
//

#include "Authenticator.hpp"

Authenticator::Authenticator() {
    this->isLoggedIn = false;
}

Authenticator::~Authenticator() {

}

bool Authenticator::IsLoggedIn() {
    return isLoggedIn;
}

bool Authenticator::CreateNewAdmin(std::string username, std::string password) {
    if (password.length()<minChars){
        return false;
    }
    
    size_t hash = hasher(password); //hash password so that in database the real password is hidden

    std::string hashPassString = std::to_string(hash); //cast to string

    Admin newAdmin = Admin(username, password); //create a new admin object

    db.insert(newAdmin); //insert the new admin object into the database
    
    return true;
}


void Authenticator::LogIn(std::string username, std::string password) {
    isLoggedIn = CheckCredentials(username, password);
}

void Authenticator::LogOut() {
    isLoggedIn = false;
}

bool Authenticator::CheckCredentials(std::string username, std::string password) {

    size_t hash = hasher(password); //hasher that hashes the password

    std::string hashPassString = std::to_string(hash); //cast the double long as a string (to match database table)

    //sql condition that will check if there is an admin with the same username and password
    admin = db.selectWhere (Admin(), {SqlCondition("userName", "=", username), SqlCondition("password", "=", password)});

    //if there is 1 then return true
    if (admin.size()==1){
        return true;
    }
    //if there is no username with associated password return false
    else {
        return false;
    }

}
