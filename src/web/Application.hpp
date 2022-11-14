//
//  Application.hpp
//

#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WString.h>
#include <Wt/WText.h>

#include <string>
#include <vector>

#include "NavbarWidget.hpp"
#include "MenuPage.hpp"
#include "OrderListPage.hpp"
#include "SalesPage.hpp"

/**
 * Class representing the Wt Application (the web server).
 * @author River Wang
 * @date 2022-10-27
 */
class Application : public Wt::WApplication {
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

   private:
    /** The navbar widget. */
    NavbarWidget *navbar;
    
    /** The body page widget. */
    Wt::WWidget *body;
};

#endif
