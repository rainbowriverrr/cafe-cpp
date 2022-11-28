//
//  Application.hpp
//

#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WString.h>
#include <Wt/WText.h>

#include <string>
#include <vector>

#include "Authenticator.hpp"
#include "CustomLoadingIndicator.hpp"
#include "NavbarWidget.hpp"
#include "HomePage.hpp"
#include "MenuPage.hpp"
#include "OrderListPage.hpp"
#include "SalesPage.hpp"
#include "CartPage.hpp"

class Authenticator;

class NavbarWidget;

/**
 * Class representing the Wt Application (the web server).
 * @author River Wang
 * @date 2022-10-27
 */
class Application : public Wt::WApplication
{
public:
    /**
     * Constructor.
     */
    Application(const Wt::WEnvironment &env);

    /**
     * Destructor.
     */
    ~Application();

    /**
     * Event handler for when the internal path is changed.
     * Sets the stack widget to the corresponding page.
     * @param internalPath The internal path that was changed to.
     */
    void handleInternalPath(const std::string &internalPath);
    
    /**
     * @brief Gets the authenticator for this session.
     *
     * @return Authenticator reference
     */
    Authenticator * getAuth();
    
    /**
     * @brief Recreates the navbar and redirects to the home page.
     *
     * To be used after logging in or out.
     */
    void reset();
    
private:
    /**
     * @brief The authenticator for this session.
     */
    Authenticator *auth;
    
    /** The navbar widget. */
    NavbarWidget *navbar;

    /** The body page widget. */
    Wt::WWidget *body;
};

#endif
