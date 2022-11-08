//
// Created by Sharon Nikritin on 2022-11-07.
//

#ifndef OrderDetail_h
#define OrderDetail_h

#include "Model.hpp"

class OrderDetail : public Model{
public:
    OrderDetail(int orderID, std::string menuItemName = "", int quantity=0);

    ~OrderDetail();

    int getOrderID();

    std::string getMenuItemName();

    int getQuantity();

    void setOrderID (int orderID);

    void setMenuItemName (std::string menuItemName);

    void setQuantity(int quantity);

protected:
    virtual std::map<std::string, std::any> toMap() override;
    virtual Model * fromMap(std::map<std::string, std::any> mMap) override;

private:
    int orderID;
    std::string menuItemName;
    int quantity;

};


#endif //OrderDetail_h
