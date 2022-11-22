//
//  CustomLoadingIndicator.hpp
//
//  Created by Julian Koksal on 2022-11-17.
//

#ifndef CustomLoadingIndicator_hpp
#define CustomLoadingIndicator_hpp

#include <Wt/WLoadingIndicator.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>

/**
 * @brief Custom loading indicator to replace the default one.
 *
 * Displays an overlayed window with the Cafe C++ logo and the text "Loading...".
 * Also overlays the page with a semi-transparent black background.
 *
 * @author Julian Koksal
 * @date 2022-11-17
 */
class CustomLoadingIndicator : public Wt::WLoadingIndicator
{
public:
    /**
     * @brief Constructor.
     *
     * Creates the widget.
     */
    CustomLoadingIndicator();
    
    /**
     * @brief Destructor.
     *
     * Does nothing.
     */
    ~CustomLoadingIndicator();
    
    /**
     * @brief Not used and does nothing. Required for override.
     *
     * @param text not used, required for override.
     */
    virtual void setMessage(const Wt::WString &text) override;
};

#endif /* CustomLoadingIndicator_hpp */
