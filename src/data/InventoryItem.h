//
// Created by Sharon Nikritin on 2022-11-07.
//

#ifndef InventoryItem_h
#define InventoryItem_h

#include "Model.hpp"

class InventoryItem: public Model{
public:
    InventoryItem(int itemID, std::string itemName = "", int quantity=0);

    ~InventoryItem();

    int getItemID();

    std::string getItemName();

    int getQuantity();

    void setItemID(int itemID);

    void setItemName (std::string itemName);

    void setQuantity (int quantity);

protected:
    virtual std::map<std::string, std::any> toMap() override;
    virtual Model * fromMap(std::map<std::string, std::any> mMap) override;

private:
    int itemID;
    std::string itemName;
    int quantity;

};


#endif //InventoryItem.h

