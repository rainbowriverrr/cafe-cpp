//
//  IOHelper.hpp
//  group8
//
//  Created by Julian Koksal on 2022-11-07.
//

#ifndef IOHelper_hpp
#define IOHelper_hpp

#include <string>
#include <fstream>

#include <Wt/WString.h>

struct IOHelper
{
public:
    static const Wt::WString readHtml(std::string fileName);
};

#endif /* IOHelper_hpp */
