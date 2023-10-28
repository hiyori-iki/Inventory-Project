#include <iostream>
#include <vector>
#include <string>

enum class ItemType { Food, Craft, Weapon, Armour };
enum class Rarity { Common, Rare, Legendary }; 

struct InventoryItem { 
    std::string name;
    ItemType type;
    Rarity rarity;
    int quantity;

    InventoryItem(const std::string& n, ItemType t, Rarity r, int q)
        : name(n), type(t), rarity(r), quantity(q) {}
};

class InventorySystem {
public:
    std::vector<InventoryItem> inventory;
    std::vector<InventoryItem> equipped;

    void addItem(const std::string& name, ItemType type, Rarity rarity, int quantity)  /*For adding the items in the datastructure
                                                                                          representing the collection of items*/
    {      
        inventory.push_back(InventoryItem(name, type, rarity, quantity));
    }

    void displayInventory()            //For displaying Inventory items
    {
        for (size_t i = 0; i < inventory.size(); ++i) {
            displayItem(inventory[i]);
        }
        std::cout <<"Inventory Size: " << inventory.size()<<"\n";
    }

    void displayEquipped()             //For displaying Equipped items
    {
        for (size_t i = 0; i < equipped.size(); ++i) {
            displayItem(equipped[i]);
        }
    }

    void displayItem(const InventoryItem& item)             /*To get the information of an item for 
                                                            the displayInventory() and displayEquipped() functions*/
    { 
        std::cout << item.name << " (" << getRarityString(item.rarity) << ")"
            << " - " << item.quantity << "x\n";
    }

    void equipItem()                         //To equip items from inventory
    {
        int itemIndex;
        std::cout << "Enter the index of the item you want to equip:";
        std::cin >> itemIndex;
        if (itemIndex >= 1 && static_cast<size_t>(itemIndex) <= inventory.size()) {
            
            int indexOfItem = doesExist(inventory[itemIndex - 1].name);
            if ( indexOfItem!= -1)              // if the item already exists we simply have to increase the quantity by one
            {
                equipped[indexOfItem].quantity++;
                inventory[itemIndex - 1].quantity--;
            }
            if ( indexOfItem== -1)            // if the item doesnt exist we will have to add the item in the equipped vector
            {
                equipped.push_back(inventory[itemIndex - 1]);
                equipped[equipped.size() - 1].quantity = 1;
                inventory[itemIndex - 1].quantity--;
            }

            
            if (inventory[itemIndex - 1].quantity == 0) {      /*If equipping items reduces the item to zero in the inventory 
                                                               this if statement will have to erase the item from its vector*/
                inventory.erase(inventory.begin() + itemIndex - 1);
            }
        }
        else {
            std::cout << "Invalid item index. Please try again.\n";
        }
    }

    void consumeItem()            //To consume food items from inventory or Equipped items section
    {
        int itemIndex;
        int choice;
        std::cout << "Consume items:\n";
        std::cout << "1.From Inventory.\n";
        std::cout << "2.From Equipped Items.\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::cout << "Enter the index of the food item to consume: ";
        std::cin >> itemIndex;

        if (choice == 1)  //to consume from inventory
        {
            if (itemIndex >= 1 && static_cast<size_t>(itemIndex) <= inventory.size()) {
               
                if (inventory[itemIndex - 1].type == ItemType::Food) {       // To check if the item you want to consume is food
                    inventory[itemIndex - 1].quantity--;

                   
                    if (inventory[itemIndex - 1].quantity == 0) {              /*If consumption reduces the quantity to 0 we will have to
                                                                                  remove the item from inventory*/
                        inventory.erase(inventory.begin() + itemIndex - 1);    
                    }
                }
                else {
                    std::cout << "Selected item is not of type Food and cannot be consumed.\n";
                }
            }
            else {
                std::cout << "Invalid item index. Please try again.\n";
            }
        }
        if (choice == 2)   //To consume from Equipped items
        {
            if (itemIndex >= 1 && static_cast<size_t>(itemIndex) <= equipped.size()) {
                
                if (equipped[itemIndex - 1].type == ItemType::Food) {
                    equipped[itemIndex - 1].quantity--;

                   
                    if (equipped[itemIndex - 1].quantity == 0) {
                        equipped.erase(equipped.begin() + itemIndex - 1);
                    }
                }
                else {
                    std::cout << "Selected item is not of type Food and cannot be consumed.\n";
                }
            }
            else {
                std::cout << "Invalid item index. Please try again.\n";
            }
        }
    }

    void dropItem()          //To reduce or drop item from inventory or equipped items section
    {
        int itemIndex;
        int choice;
        std::cout << "Drop Items:\n";
        std::cout << "1.From Inventory.\n";
        std::cout << "2.From Equipped Items.\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << "Enter the index of the item to drop: ";
        std::cin >> itemIndex;
        

        if ( choice==1) {         // to drop items from inventory
            if (itemIndex >= 1 && static_cast<size_t>(itemIndex) <= inventory.size())
            {
                inventory[itemIndex - 1].quantity--;
             
                if (inventory[itemIndex - 1].quantity == 0) {
                    inventory.erase(inventory.begin() + itemIndex - 1);
                }
            }
            else {
                std::cout << "Invalid item index. Please try again.\n";
            }
        }
        if (choice == 2)     //to drop items from equipped items
        {
            if (itemIndex >= 1 && static_cast<size_t>(itemIndex) <= equipped.size())
            {
                equipped[itemIndex - 1].quantity--;

                if (equipped[itemIndex - 1].quantity == 0) {
                    equipped.erase(equipped.begin() + itemIndex - 1);
                }
            }
            else {
                std::cout << "Invalid item index. Please try again.\n";
            }
        }
      
    }

    std::string getRarityString(Rarity rarity) /*This function is to handle the rarity enumeration values
                                                 Common, Rare, and Legendary */
    {
        switch (rarity) {
        case Rarity::Common: return "Common";
        case Rarity::Rare: return "Rare";
        case Rarity::Legendary: return "Legendary";
        }
        return "Unknown";
    }

    int doesExist(std::string item)        /* To check if the same item already exists in the equipped section
                                             if the item exists it will return the index of them equipped item*/
    {
        for (int i = 0; i < equipped.size(); ++i)
        {
            if (equipped[i].name == item)
            {
                return i;
            }
        }
        return -1;
    }

};

int main() {
    InventorySystem inventory;
    inventory.addItem("Beef", ItemType::Food, Rarity::Common, 5);  
    inventory.addItem("Pork", ItemType::Food, Rarity::Rare, 3);
    inventory.addItem("Wooden Planks", ItemType::Craft, Rarity::Rare, 3);
    inventory.addItem("Ebon Axe", ItemType::Weapon, Rarity::Legendary, 1);
    inventory.addItem("Defender", ItemType::Armour, Rarity::Common, 3);

    while (true) {
        int choice;
        std::cout << "Inventory System Menu:\n";
        std::cout << "1. Display Inventory\n";
        std::cout << "2. Display Equipped\n";
        std::cout << "3. Equip Item\n";
        std::cout << "4. Consume Item\n";
        std::cout << "5. Drop Item\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            inventory.displayInventory();
        }
        else if (choice == 2) {
            inventory.displayEquipped();
        }
        else if (choice == 3) {
            inventory.equipItem();
        }
        else if (choice == 4) {
            inventory.consumeItem();
        }
        else if (choice == 5) {
            inventory.dropItem();
        }
        else if (choice == 6) {
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

