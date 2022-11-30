/*
    Author : Daniel McGarr
    Date   : 2022/11/22
*/

#include "InventoryPage.hpp"

InventoryPage::InventoryPage() {

    std::vector<InventoryItem> inventoryItems = DBHelper::getInstance().selectWhere(InventoryItem());
    addStyleClass("list");
    Wt::WContainerWidget *inventoryListWidget = addNew<WContainerWidget>();
    
    
    inventoryListWidget->addNew<Wt::WTemplate>(tr("inventory-page"));
    
    
    for (std::vector<InventoryItem>::iterator it = inventoryItems.begin(); it != inventoryItems.end(); it++) {
    	inventoryListWidget->addWidget(createListItemWidget(inventoryListWidget, *it));
    }
}

InventoryPage::~InventoryPage() {
}

void InventoryPage::onUpdateInventoryBtnClicked(Wt::WTemplate *listItem, Wt::WContainerWidget *inventoryListContainer, InventoryItem item, Wt::WLineEdit* const qty){
	std::string quant = qty->text().toUTF8();
        if (qty->hasSelectedText()){
        	int quantity = stoi(quant);
        	item.setQuantity(quantity);
        	DBHelper::getInstance().update(item);
        	listItem->bindWidget("Item-quantity", std::make_unique<Wt::WText>("Quantity: " +  quant));
        }
}

std::unique_ptr<Wt::WTemplate> InventoryPage::createListItemWidget(Wt::WContainerWidget *inventoryListContainer, InventoryItem inv)
{
	std::unique_ptr<Wt::WTemplate> item = std::make_unique<Wt::WTemplate>(tr("inventory-item"));
	int id = inv.getItemID();
        std::string name = inv.getItemName();
        int quantity = inv.getQuantity();
        
        std::stringstream ss;
        ss << id;
        std::string idStr = ss.str();
        ss<< quantity;
        std::string quantityStr = ss.str();
        
        item->bindWidget("Item-ID", std::make_unique<Wt::WText>("Item ID: "+ idStr));
        item->bindWidget("Item-name", std::make_unique<Wt::WText>(name));
        item->bindWidget("Item-quantity", std::make_unique<Wt::WText>("Quantity: " +  quantityStr));
        auto new_quantity = item->bindWidget("Update-field", std::make_unique<Wt::WLineEdit>());
        Wt::WPushButton *button = item->bindWidget("Update-btn", std::make_unique<Wt::WPushButton>("Update Quantity"));
        
        Wt::WTemplate *itemPtr = item.get();
        
        
        
        button->clicked().connect([this, itemPtr, inventoryListContainer, inv, new_quantity]{ onUpdateInventoryBtnClicked(itemPtr, inventoryListContainer, inv, new_quantity); });
        
        return item;
}
