//
//  vOrderDetail.hpp
//

#ifndef vOrderDetail_hpp
#define vOrderDetail_hpp

#include <string>
#include <map>

#include "Model.hpp"

/**
 * @brief Class representing a row of the vOrderDetail view.
 *
 * @author Julian Koksal
 * @date 2022-11-08
 */
class vOrderDetail : public Model
{
public:
    /**
     * @brief Constructor.
     *
     * Creates an object initialized with the given values.
     *
     * @param orderDetailID the value to initialize orderDetailID with
     * @param orderNumber the value to initialize orderNumber with
     * @param menuItemName the value to initialize menuItemName with
     * @param quantity the value to initialize quantity with
     * @param price the value to initialize price with
     * @param total the value to initialize total with
     */
    vOrderDetail(int orderDetailID = 0, int orderNumber = 0, std::string menuItemName = "", int quantity = 0, double price = 0, double total = 0);

    /**
     * @brief Destructor.
     *
     * Does nothing.
     */
    ~vOrderDetail();
    
    /**
     * @brief Gets orderDetailID.
     *
     * @return orderDetailID
     */
    int getOrderDetailID();
    
    /**
     * @brief Gets orderNumber.
     *
     * @return orderNumber
     */
    int getOrderNumber();
    
    /**
     * @brief Gets menuItemName.
     *
     * @return menuItemName
     */
    std::string getMenuItemName();
    
    /**
     * @brief Gets quantity.
     *
     * @return quantity
     */
    int getQuantity();
    
    /**
     * @brief Gets price.
     *
     * @return price
     */
    double getPrice();
    
    /**
     * @brief Gets total.
     *
     * @return total
     */
    double getTotal();

private:
    /**
     * @brief The ID of the OrderDetail.
     */
    int orderDetailID;
    
    /**
     * @brief The order number of the OrderMaster this detail belongs to.
     */
    int orderNumber;
    
    /**
     * @brief The name of the menu item.
     */
    std::string menuItemName;
    
    /**
     * @brief The quantity of the menu item in the order.
     */
    int quantity;
    
    /**
     * @brief The price of the menu item.
     */
    double price;
    
    /**
     * @brief The total price, equal to quantity multiplied by price.
     */
    double total;
    
    virtual std::string tableName() const override;
    virtual std::vector<std::string> columns() const override;
    virtual std::set<std::string> keys() const override;
    virtual bool isAutoGeneratedKey() const override;
    virtual std::map<std::string, std::any> toMap() const override;
    virtual Model * fromMap(std::map<std::string, std::any> mMap) const override;
};

#endif /* vOrderDetail_hpp */
