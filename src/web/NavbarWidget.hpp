//
//  NavbarWidget.hpp
//

#ifndef NavbarWidget_hpp
#define NavbarWidget_hpp

#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WAnchor.h>
#include <Wt/WImage.h>

/**
 * @brief Class representing the navbar widget.
 *
 * Displays a navigation bar at the top of the page with button links to each page of the website.
 * Different pages are displayed depending on if the user is logged in or not. (NOT IMPLEMENTED YET)
 *
 * @author Julian Koksal
 * @date 2022-11-07
 */
class NavbarWidget : public Wt::WContainerWidget
{
public:
    /**
     * @brief Constructor.
     *
     * Creates the widget and its contents.
     */
    NavbarWidget();
    
    /**
     * @brief Destructor.
     *
     * Does nothing.
     */
    ~NavbarWidget();
};

#endif /* NavbarWidget_hpp */
