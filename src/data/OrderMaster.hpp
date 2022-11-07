//
//  OrderMaster.hpp
//
//  Created by Julian Koksal on 2022-11-07.
//

#ifndef OrderMaster_hpp
#define OrderMaster_hpp

#include <string>
#include <map>

#include "Model.hpp"

class OrderMaster : public Model
{
public:
    OrderMaster(int orderNumber = 0, std::string orderedBy = "", std::string orderedDate = "", bool isComplete = 0);
    
    ~OrderMaster();
        
    int getOrderNumber();
    std::string getOrderedBy();
    std::string getOrderDate();
    bool getIsComplete();
    
    void setOrderedBy(std::string val);
    void setOrderDate(std::string val);
    void setIsComplete(bool val);
protected:
    virtual std::map<std::string, std::any> toMap();
    virtual Model * fromMap(std::map<std::string, std::any> mMap);
private:
    int orderNumber;
    std::string orderedBy;
    std::string orderDate;
    bool isComplete;
};

#endif /* OrderMaster_hpp */
