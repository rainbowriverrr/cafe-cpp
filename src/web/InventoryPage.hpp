/*
    Author : Daniel McGarr
    Date   : 2022/11/22
*/

#ifndef InventoryPage_h
#define InventoryPage_h

#include <string>

#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>
#include <Wt/WPanel.h>
#include <Wt/WTable.h>
#include <Wt/WPushButton.h>
#include <Wt/WLink.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WFlags.h>
#include <Wt/WAnimation.h>

#include "DBHelper.hpp"
#include "OrderMaster.hpp"
#include "vOrderDetail.hpp"
#include "Page.hpp"
#include "Application.hpp"
#include "InventoryItem.hpp"

class InventoryPage : public Wt::WContainerWidget {
   public:
    /**
     * @brief Construct a new Inventory Page object
     *
     */
    InventoryPage();

    /**
     * @brief Destroy the Inventory Page object
     *
     */
    ~InventoryPage();
    
    std::unique_ptr<Wt::WTemplate> createListItemWidget(Wt::WContainerWidget *inventoryListContainer, InventoryItem inv);
    
    void onUpdateInventoryBtnClicked(Wt::WTemplate *listItem, Wt::WContainerWidget *inventoryListContainer, InventoryItem item, Wt::WLineEdit* const qty);
};

#endif
