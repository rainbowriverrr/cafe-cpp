/*
    Author : River Wang
    Date   : 2022/11/19
*/

#ifndef CartPage_hpp
#define CartPage_hpp

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>

#include "OrderDetail.hpp"
#include "OrderMaster.hpp"

class CartPage : public Wt::WContainerWidget {
   public:
    /**
     * @brief Construct a new Cart Page object
     *
     */
    CartPage();

    /**
     * @brief Destroy the Cart Page object
     *
     */
    ~CartPage();
}

#endif