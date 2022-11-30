/*
    Author : River Wang
    Date   : 2022/11/19
*/

#ifndef CartPage_hpp
#define CartPage_hpp

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>

#include <string>

#include "CartWidget.hpp"
#include "DBHelper.hpp"
#include "MenuItem.hpp"
#include "Model.hpp"
#include "OrderDetail.hpp"
#include "OrderMaster.hpp"
#include "SqlCondition.hpp"

class CartPage : public Wt::WContainerWidget {
   public:
    /**
     * @brief Construct a new Cart Page object
     *
     */
    CartPage();

    /**
     * @brief get cartTotal pointer
     *
     */
    CartTotal *getCartTotalPtr();

    /**
     * @brief Destroy the Cart Page object
     *
     */
    ~CartPage();

   private:
    /**
     * @brief CartTotal widget
     *
     */
    CartTotal *cartTotal;
};

#endif