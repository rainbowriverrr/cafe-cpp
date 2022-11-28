//
//  Page.cpp
//
//  Created by Julian Koksal on 2022-11-22.
//

#include "Page.hpp"

Page::Page()
{
    
}

Page::~Page()
{
    
}

std::string Page::formatPrice(const double &price)
{
    std::ostringstream ss;
    ss << std::setprecision(2) << std::fixed << "$ " << price;
    return ss.str();
}
