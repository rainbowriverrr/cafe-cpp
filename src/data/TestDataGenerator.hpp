//
//  TestDataGenerator.hpp
//

#ifndef TestDataGenerator_hpp
#define TestDataGenerator_hpp

#include <string>
#include <vector>
#include <cmath>

#include <Wt/WDateTime.h>
#include <Wt/WRandom.h>

#include "DBHelper.hpp"
#include "OrderMaster.hpp"
#include "OrderDetail.hpp"

/**
 * @brief Contains methods to generate test data and insert it to the database.
 *
 * @author Julian Koksal
 * @date 2022-11-16
 */
class TestDataGenerator
{
public:
    static void generateOrders();
private:
    TestDataGenerator();
    ~TestDataGenerator();
};

#endif /* TestDataGenerator_hpp */
