//
//  IOHelper.cpp
//
//  Created by Julian Koksal on 2022-11-07.
//

#include "IOHelper.hpp"

const Wt::WString IOHelper::readHtml(std::string fileName)
{
    std::string html = "";
    
    std::ifstream in;
    in.open("resources/" + fileName);
    if (in.is_open())
    {
        html.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    }
    in.close();
    
    return Wt::WString(html);
}
