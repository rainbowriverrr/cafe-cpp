//
//  CustomLoadingIndicator.cpp
//  group8
//
//  Created by Julian Koksal on 2022-11-17.
//

#include "CustomLoadingIndicator.hpp"

CustomLoadingIndicator::CustomLoadingIndicator()
{
    setImplementation(std::make_unique<Wt::WTemplate>(tr("loading-indicator")));
}

CustomLoadingIndicator::~CustomLoadingIndicator()
{
    
}

void CustomLoadingIndicator::setMessage(const Wt::WString &text)
{
    
}
