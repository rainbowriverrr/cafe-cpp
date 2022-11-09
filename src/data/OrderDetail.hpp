//
// Created by Sharon Nikritin on 2022-11-07.
//

#ifndef OrderDetail_hpp
#define OrderDetail_hpp

#include <string>
#include <map>

#include "Model.hpp"

class OrderDetail : public Model
{
public:
    OrderDetail(int orderDetailID = 0, int orderNumber = 0, std::string menuItemName = "", int quantity = 0);

    ~OrderDetail();
    
    int getOrderDetailID();

    int getOrderNumber();

    std::string getMenuItemName();

    int getQuantity();

    void setOrderNumber(int orderNumber);

    void setMenuItemName (std::string menuItemName);

    void setQuantity(int quantity);

protected:
    virtual std::map<std::string, std::any> toMap() const override;
    virtual Model * fromMap(std::map<std::string, std::any> mMap) const override;

private:
    int orderDetailID;
    int orderNumber;
    std::string menuItemName;
    int quantity;

};


#endif //OrderDetail_hpp
