//
//  MenuItem.hpp
//

#ifndef MenuItem_hpp
#define MenuItem_hpp

#include <map>
#include <string>

#include "Model.hpp"

/**
 * Class representing a row of the MenuItem table.
 * @author Julian Koksal
 * @date 2022-09-25
 */
class MenuItem : public Model {
   public:
    /**
     * Constructor creates a MenuItem with the given values.
     * @param name The name of the MenuItem.
     * @param price The price of the MenuItem.
     */
    MenuItem(std::string name = "", double price = 0);

    /**
     *Constructor creates a MenuItem with name, price, and description.
     * @param name The name of the MenuItem.
     * @param price The price of the MenuItem.
     * @param description The description of the MenuItem.
     */
    MenuItem(std::string name, double price, std::string description);

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

    /**
     * Gets the description.
     * @return description
     */
    std::string getDescription();

    /**
     * @brief Sets the description of the item
     * @param description The new description.
     */
    void setDescription(std::string description);

   protected:
    virtual std::map<std::string, std::any> toMap() const override;
    virtual Model* fromMap(std::map<std::string, std::any> mMap) const override;

   private:
    /** The name of the MenuItem. */
    std::string name;

    /** The price of the MenuItem. */
    double price;

    /** The description of the menu item*/
    std::string description;
};

#endif /* MenuItem_hpp */
