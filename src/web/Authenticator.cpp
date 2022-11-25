//
// Created by Sharon Nikritin on 2022-11-17.
//

#include "Authenticator.hpp"

Authenticator::Authenticator() {

}

Authenticator::~Authenticator() {

}

bool Authenticator::IsLoggedIn() {
    return isLoggedIn;
}

void Authenticator::CreateNewAdmin(std::string username, std::string password) {
    size_t hash = hasher(password);

    if (hash> INT_MAX){
        throw std::overflow_error("the password is too large");
    }

    int hashPass = static_cast<int> (hash);
    std::string hashPassString = std::to_string(hashPass);

    Admin newAdmin = Admin(username, password);

    db.insert(newAdmin);
}

void Authenticator::LogIn(std::string username, std::string password) {
    isLoggedIn = CheckCredentials(username, password);
}

bool Authenticator::CheckCredentials(std::string username, std::string password) {
    size_t hash = hasher(password);

    int hashPass = static_cast<int>(hash);
    std::string hashPassString = std::to_string(hashPass);

    admin = db.selectWhere (Admin(), {SqlCondition("userName", "=", username), SqlCondition("password", "=", password)});

    if (admin.size()==1){
        return true;
    }
    else {
        return false;
    }

}