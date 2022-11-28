//
//  HomePage.hpp
//

#ifndef HomePage_hpp
#define HomePage_hpp

#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>

/**
 * @brief Class representing the home page.
 *
 * @author Julian Koksal
 * @date 2022-11-28
 */
class HomePage : public Wt::WContainerWidget
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
