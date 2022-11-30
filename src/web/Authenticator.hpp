/**
 * @brief can create a new admin object and put the admin into the database (username and a
 * hashed password) can login as an exsiting admin that was already in database
 * @author Sharon Nikritin
 */

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

    /**
     * @brief constructor of authenticator
     * does not take any parameters just creates an authenticator object that can later use
     * authenticator methods
     */
    Authenticator();

    /**
    * @brief destructor of authenticator
    */
    ~Authenticator();

    /**
     * @brief returns whether an authenticator has a an admin who has logged into the system as an admin
     * @return isLoggedIn - bool that represents if a user is logged in
     */
    bool IsLoggedIn ();

    /**
     * @brief creates a new administrator and adds the new admin in the database if the password is larger than 9 characters
     * @param username - string that represents the admins wanted username
     * @param password -  string that represents the admins password that they want to create
     * @return bool - if the password of admin is larger than 9 then return true, else false
     */
    bool CreateNewAdmin (std:: string username, std::string password);

    /**
     * @brief log out of current admin in the administrator
     */
    void LogOut();

    /**
     * @brief stores a boolean that shows if username and password is correct and in database (using another method)
     * @param username - string that represents the admins username
     * @param password - string that represents the admins password
     */
    void LogIn(std::string username, std::string password);

private:
    /**
     * @brief minimum password length
     */
    int minChars = 9;
    /**
     * @brief boolean that represents if a there is a current admin logged in
     */
    bool isLoggedIn;
    /**
     * @brief private method that is used by other method that checks if the password and username match in the database
     * @param username - string that represents the username of admin
     * @param password - string that represents the admins password
     * @return bool that will represent if the credentials match what is in the database
     */
    bool CheckCredentials (std::string username, std::string password);
    /**
     * @brief Singleton instance of the db helper
     */
    const DBHelper &db = DBHelper::getInstance();
    /**
     * @brief hasher object to hash the users passwords
     */
    std::hash<std::string> hasher;
    /**
     * @brief vector of admins that will be returned by the check credentials method
     */
    std::vector<Admin> admin;


};


#endif //Authenicator.hpp
