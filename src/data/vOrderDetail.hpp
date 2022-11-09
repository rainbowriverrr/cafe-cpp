//
//  vOrderDetail.hpp
//

#ifndef vOrderDetail_hpp
#define vOrderDetail_hpp

#include <string>
#include <map>

#include "Model.hpp"

/**
 * @author Julian Koksal
 * @date 2022-11-08
 */
class vOrderDetail : public Model
{
public:
    vOrderDetail(int orderDetailID = 0, int orderNumber = 0, std::string menuItemName = "", int quantity = 0, double price = 0, double total = 0);

    ~vOrderDetail();
    
    int getOrderDetailID();
    
    int getOrderNumber();
    
    std::string getMenuItemName();
    
    int getQuantity();
    
    double getPrice();
    
    double getTotal();
protected:
    virtual std::map<std::string, std::any> toMap() const override;
    virtual Model * fromMap(std::map<std::string, std::any> mMap) const override;
private:
    int orderDetailID;
    
    int orderNumber;
    
    std::string menuItemName;
    
    int quantity;
    
    double price;
    
    double total;
};

#endif /* vOrderDetail_hpp */
