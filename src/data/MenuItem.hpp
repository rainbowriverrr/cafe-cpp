//
//  MenuItem.hpp
//  DAL Test
//
//  Created by Julian Koksal on 2022-09-25.
//

#ifndef MenuItem_hpp
#define MenuItem_hpp

#include "Model.hpp"

class MenuItem : public Model
{
public:
    MenuItem(std::string name = "", double price = 0);
    
    ~MenuItem();
        
    std::string getName();
    double getPrice();
    
    void setPrice(double price);
protected:
    virtual std::map<std::string, std::any> toMap() const;
    virtual Model * fromMap(std::map<std::string, std::any> mMap) const;
private:
    std::string name;
    double price;
};

#endif /* MenuItem_hpp */
