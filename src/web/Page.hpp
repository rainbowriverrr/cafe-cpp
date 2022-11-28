//
//  Page.hpp
//

#ifndef Page_hpp
#define Page_hpp

#include <sstream>
#include <iomanip>
#include <string>

#include <Wt/WContainerWidget.h>

/**
 * @brief Base class extended by the page widgets.
 *
 * Implements common methods that are useful across multiple pages.
 *
 * @author Julian Koksal
 * @date 2022-11-22
 */
class Page : public Wt::WContainerWidget
{
public:
    /**
     * @brief Destructor.
     *
     * Does nothing.
     */
    virtual ~Page();
protected:
    /**
     * @brief Constructor.
     *
     * Protected because Page is not intended to be initialized, only extended.
     */
    Page();
    
    /**
     * @brief Formats the given price double as a string.
     *
     * e.g. 2.290000 -> "$ 2.29"
     *
     * @param price the price as a double
     * @return the price formatted as a string
     */
    static std::string formatPrice(const double &price);
};

#endif /* Page_hpp */
