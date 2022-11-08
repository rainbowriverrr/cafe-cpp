//
// Created by Sharon Nikritin on 2022-11-07.
//

#ifndef menuItemIngredient_h
#define menuItemIngredient_h

#include "Model.hpp"


class MenuItemIngredient : public Model{
public:
    MenuItemIngredient(std::string menuItemName="", int inventoryItemID, int quantity = 0);

    ~MenuItemIngredient();

    std::string getMenuItemName();

    int getInventoryItemID();

    int getQuantity();

    void setMenuItemName(std::string menuItemName);

    void setInventoryItemID (int inventoryItemID);

    void setQuantity (int quantity);

protected:
    virtual std::map<std::string, std::any> toMap() override;
    virtual Model * fromMap(std::map<std::string, std::any> mMap) override;

private:
    std::string menuItemName;
    int inventoryItemID;
    int quantity;

};


#endif //menuItemIngredient_h

