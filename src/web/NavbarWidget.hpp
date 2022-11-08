//
//  NavbarWidget.hpp
//

#ifndef NavbarWidget_hpp
#define NavbarWidget_hpp

#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WAnchor.h>
#include <Wt/WImage.h>

#include "IOHelper.hpp"

/**
 * Class representing the navbar widget.
 * @author Julian Koksal
 * @date 2022-11-07
 */
class NavbarWidget : public Wt::WContainerWidget
{
public:
    /**
     * Constructor.
     */
    NavbarWidget();
    
    /**
     * Destructor.
     */
    ~NavbarWidget();
};

#endif /* NavbarWidget_hpp */
