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

    void addItem(const std::string& name, ItemType type, Rarity rarity, int quantity) {
        inventory.push_back(InventoryItem(name, type, rarity, quantity));
    }

    void displayInventory() {
        // Display inventory items
        for (size_t i = 0; i < inventory.size(); ++i) {
            displayItem(inventory[i]);
        }
        std::cout <<"Inventory Size: " << inventory.size()<<"\n";
    }

    void displayEquipped() {
        // Display equipped items
        for (size_t i = 0; i < equipped.size(); ++i) {
            displayItem(equipped[i]);
        }
    }

    void displayItem(const InventoryItem& item) {
        std::cout << item.name << " (" << getRarityString(item.rarity) << ")"
            << " - " << item.quantity << "x\n";
    }

    void equipItem()
    {
        int itemIndex;
        std::cout << "Enter the index of the item you want to equip:";
        std::cin >> itemIndex;
        if (itemIndex >= 1 && static_cast<size_t>(itemIndex) <= inventory.size()) {
            
            int indexOfItem = doesExist(inventory[itemIndex - 1].name);
            if ( indexOfItem!= -1)
            {
                equipped[indexOfItem].quantity++;
                inventory[itemIndex - 1].quantity--;
            }
            if ( indexOfItem== -1)
            {
                equipped.push_back(inventory[itemIndex - 1]);
                equipped[equipped.size() - 1].quantity = 1;
                inventory[itemIndex - 1].quantity--;
            }

            
            if (inventory[itemIndex - 1].quantity == 0) {
                inventory.erase(inventory.begin() + itemIndex - 1);
            }
        }
        else {
            std::cout << "Invalid item index. Please try again.\n";
        }
    }

    void consumeItem()
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

        if (choice == 1)
        {
            if (itemIndex >= 1 && static_cast<size_t>(itemIndex) <= inventory.size()) {
               
                if (inventory[itemIndex - 1].type == ItemType::Food) {
                    inventory[itemIndex - 1].quantity--;

                   
                    if (inventory[itemIndex - 1].quantity == 0) {
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
        if (choice == 2)
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

    void dropItem()
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
        

        if ( choice==1) {
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
        if (choice == 2)
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

    std::string getRarityString(Rarity rarity) {
        switch (rarity) {
        case Rarity::Common: return "Common";
        case Rarity::Rare: return "Rare";
        case Rarity::Legendary: return "Legendary";
        }
        return "Unknown";
    }

    int doesExist(std::string item)
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

