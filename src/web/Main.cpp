//
//  Main.cpp
//
//  Created by Julian Koksal on 2022-11-05.
//

#include <Wt/WApplication.h>

#include "Application.hpp"

#include "TestDataGenerator.hpp"

/**
 * Main method runs the Wt Application.
 */
int main(int argc, char **argv) {
    TestDataGenerator::generateOrders();
    
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
        return std::make_unique<Application>(env);
    });
}
