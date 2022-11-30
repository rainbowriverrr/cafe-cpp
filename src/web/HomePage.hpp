//
//  HomePage.hpp
//

#ifndef HomePage_hpp
#define HomePage_hpp

#include <Wt/WTemplate.h>

#include "Page.hpp"

/**
 * @brief Class representing the home page.
 *
 * @author Julian Koksal
 * @date 2022-11-28
 */
class HomePage : public Page
{
public:
    /**
     * @brief Constructor.
     *
     * Creates the page widget and its contents.
     */
    HomePage();
    
    /**
     * @brief Destructor.
     *
     * Does nothing.
     */
    ~HomePage();
};

#endif /* HomePage_hpp */
