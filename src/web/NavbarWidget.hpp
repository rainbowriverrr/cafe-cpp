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
 * Different links are displayed depending on if the user is logged in or not.
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
private:
    /**
     * @brief Creates and returns the navbar widget as it appears to customers (not logged in).
     *
     * Has links to the home, menu, orders, login, and cart pages.
     *
     * @return unique ptr to the widget that was created
     */
    std::unique_ptr<Wt::WTemplate> createCustomerNavbarWidget();
    
    /**
     * @brief Creates and returns the navbar widget as it appears to administrators (logged in).
     *
     * Has links to the home, menu, orders, sales, inventory, and create account pages, and a link to log out.
     *
     * @return unique ptr to the widget that was created
     */
    std::unique_ptr<Wt::WTemplate> createAdminNavbarWidget();
    
    /**
     * @brief Binds the anchor widgets that are common to both the customer navbar and admin navbar.
     *
     * Binds the anchor to the home, menu, and orders pages.
     *
     * @param navTemplate the navbar template to bind the anchors to
     */
    void bindCommonNavbarAnchors(Wt::WTemplate *navTemplate);
};

#endif /* NavbarWidget_hpp */
