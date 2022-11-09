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

#include "DBHelper.hpp"
#include "IOHelper.hpp"
#include "MenuItem.hpp"
#include "MenuPage.hpp"
#include "NavbarWidget.hpp"
#include "OrderListPage.hpp"
#include "OrderMaster.hpp"

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
    /** The container widget that contains the entire application. */
    Wt::WContainerWidget *page;

    /** The navbar widget. */
    NavbarWidget *navbar;

    /** The stack widget that contains the body of the pages. */
    Wt::WStackedWidget *stack;

    /** The home page widget. */
    Wt::WText *pageHome;

    /** The menu page widget. */
    MenuPage *pageMenu;

    /** The order list page widget. */
    OrderListPage *pageOrderList;
};

#endif
