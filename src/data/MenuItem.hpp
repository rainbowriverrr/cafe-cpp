//
//  MenuItem.hpp
//

#ifndef MenuItem_hpp
#define MenuItem_hpp

#include <string>
#include <map>

#include "Model.hpp"

/**
 * Class representing a row of the MenuItem table.
 * @author Julian Koksal
 * @date 2022-09-25
 */
class MenuItem : public Model
{
public:
    /**
     * Constructor creates a MenuItem with the given values.
     * @param name The name of the MenuItem.
     * @param price The price of the MenuItem.
     */
    MenuItem(std::string name = "", double price = 0);
    
    /**
     * Destructor.
     */
    ~MenuItem();
    
    /**
     * Gets the name.
     * @return name
     */
    std::string getName();
    
    /**
     * Gets the price.
     * @return price
     */
    double getPrice();
    
    /**
     * Sets the price.
     * @param price The new price.
     */
    void setPrice(double price);
protected:
    virtual std::map<std::string, std::any> toMap() const override;
    virtual Model * fromMap(std::map<std::string, std::any> mMap) const override;
private:
    /** The name of the MenuItem. */
    std::string name;
    
    /** The price of the MenuItem. */
    double price;
};

#endif /* MenuItem_hpp */
