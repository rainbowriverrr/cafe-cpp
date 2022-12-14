//
//  MenuItem.hpp
//

#ifndef MenuItem_hpp
#define MenuItem_hpp

#include <map>
#include <string>

#include "Model.hpp"

/**
 * @brief Class representing a row of the MenuItem table.
 *
 * @author Julian Koksal
 * @date 2022-09-25
 */
class MenuItem : public Model
{
public:
    /**
     * @brief Constructor.
     *
     * Creates an object with name, price, and description.
     *
     * @param name The name of the MenuItem.
     * @param price The price of the MenuItem.
     * @param description The description of the MenuItem.
     */
    MenuItem(std::string name = "", double price = 0, std::string description = "");

    /**
     * @brief Destructor.
     *
     * Does nothing.
     */
    ~MenuItem();

    /**
     * @brief Gets the name.
     *
     * @return name
     */
    std::string getName();

    /**
     * @brief Gets the price.
     *
     * @return price
     */
    double getPrice();
    
    /**
     * @brief Gets the description.
     *
     * @return description
     */
    std::string getDescription();

    /**
     * @brief Sets the price.
     * 
     * @param price The new price.
     */
    void setPrice(double price);

    /**
     * @brief Sets the description of the item
     *
     * @param description The new description.
     */
    void setDescription(std::string description);
    
private:
    /** The name of the MenuItem. */
    std::string name;

    /** The price of the MenuItem. */
    double price;
    
    /** The description of the menu item*/
    std::string description;
    
    virtual std::string tableName() const override;
    virtual std::vector<std::string> columns() const override;
    virtual std::set<std::string> keys() const override;
    virtual bool isAutoGeneratedKey() const override;
    virtual std::map<std::string, std::any> toMap() const override;
    virtual Model * fromMap(std::map<std::string, std::any> mMap) const override;
};

#endif /* MenuItem_hpp */
