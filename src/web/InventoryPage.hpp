/**
 * Class representing the Wt Inventory Page.
 * @author Daniel McGarr
 * @date 2022-10-28
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
    
    
    /**
     * @brief creates widges for each item in the inventory and displays them on the webpage
     * @Param inventoryListContainer, is the widget container used for the Inventory Page
     * @Param InventoryItem is the item to be displayed on the webpage
     */
    std::unique_ptr<Wt::WTemplate> createListItemWidget(Wt::WContainerWidget *inventoryListContainer, InventoryItem inv);
    
    /**
     * @brief updates database and widget when the update button is pressed.
     * @Param listItem is the WTemplate used to display the changes when the quantity is updated
     * @Param inventoryListContainer is the widget container used for the inventory page
     * @Param Inventory Item is the item being updated
     * @Param qty is the line from the input, representing the new updated quantity.
     */
    void onUpdateInventoryBtnClicked(Wt::WTemplate *listItem, Wt::WContainerWidget *inventoryListContainer, InventoryItem item, Wt::WLineEdit* const qty);
};

#endif
