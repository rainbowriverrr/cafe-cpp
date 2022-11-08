//
//  NavbarWidget.hpp
//
//  Created by Julian Koksal on 2022-11-07.
//

#ifndef NavbarWidget_hpp
#define NavbarWidget_hpp

#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WAnchor.h>
#include <Wt/WImage.h>

#include "IOHelper.hpp"

class NavbarWidget : public Wt::WContainerWidget
{
public:
    NavbarWidget();
    ~NavbarWidget();
};

#endif /* NavbarWidget_hpp */
