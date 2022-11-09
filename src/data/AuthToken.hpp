//
// Created by Sharon Nikritin on 2022-11-05.
//

#ifndef AuthToken_hpp
#define AuthToken_hpp

#include <string>
#include <map>

#include "Model.hpp"

class AuthToken : public Model
{
public:
    AuthToken (std::string tokenID, std::string createdDate);

    ~AuthToken ();

    std::string getTokenID ();

    bool isValid();

protected:
    virtual std::map<std::string, std::any> toMap() const override;
    virtual Model * fromMap(std::map<std::string, std::any> mMap) const override;

private:
    std::string tokenID;
    std::string createdDate;
};


#endif //AuthToken_hpp

