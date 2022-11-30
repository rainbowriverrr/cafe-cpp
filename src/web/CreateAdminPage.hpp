//
//  CreateAdminPage.hpp
//

#ifndef CreateAdminPage_hpp
#define CreateAdminPage_hpp

#include <Wt/WTemplate.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

#include <ctime>
#include <string>

#include "Application.hpp"
#include "Authenticator.hpp"
#include "Page.hpp"

/**
 * @brief Class representing the create admin page.
 *
 * @author Alex Mihas
 */
class CreateAdminPage : public Page {
   public:
    /**
     * @brief Construct a new Admin Page object
     *
     */
    CreateAdminPage();

    /**
     * @brief Destroy the Admin Page object
     *
     */
    ~CreateAdminPage();
};

#endif /* CreateAdminPage_hpp */
