//
// Created by Sharon Nikritin on 2022-11-05.
//

#ifndef AuthToken_h
#define AuthToken_h

#include "Model.hpp"

class AuthToken : public Model {
public:
    AuthToken (std::string tokenID, time_t createdDate);

    ~AuthToken ();

    std::string getTokenID ();

    bool isValid();

protected:
    virtual std::map<std::string, std::any> toMap() override;
    virtual Model * fromMap(std::map<std::string, std::any> mMap) override;

private:
    std::string tokenID;
    time_t createdDate;
};


#endif //AuthToken_h

