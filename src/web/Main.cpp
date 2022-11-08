//
//  Main.cpp
//
//  Created by Julian Koksal on 2022-11-05.
//

#include <Wt/WApplication.h>

#include "Application.hpp"

/**
 * Main method runs the Wt Application.
 */
int main(int argc, char **argv) {
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
        return std::make_unique<Application>(env);
    });
}
