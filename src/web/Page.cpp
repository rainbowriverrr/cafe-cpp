//
//  Page.cpp
//
//  Created by Julian Koksal on 2022-11-22.
//

#include "Page.hpp"

const Wt::WString Page::formatPrice(const double &price)
{
    std::ostringstream ss;
    ss << std::setprecision(2) << std::fixed << "$ " << price;
    return Wt::WString(ss.str());
}
