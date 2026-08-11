#include "Loot.h"

#include <iostream>
#include <utility>

int main()
{
    std::cout << "=== ORIGINAL CONTAINER ===\n";

    LootContainer original_loot(3);

    original_loot.AddItem({"Iron Sword", 50});
    original_loot.AddItem({"Health Potion", 25});
    original_loot.AddItem({"Gold Ring", 100});

    original_loot.DisplayItems();

    std::cout << "\n\n=== FULL CONTAINER TEST ===\n";

    bool item_added = original_loot.AddItem({"Diamond", 500});

    if(!item_added)
    {
        std::cout << "Could not add Diamond: container is full.\n";
    }

    std::cout << "\n=== COPY CONSTRUCTOR ===\n";

    LootContainer copied_loot(original_loot);
    copied_loot.DisplayItems();

    std::cout << "\n\n=== COPY ASSIGNMENT ===\n";

    LootContainer assigned_loot(1);
    assigned_loot.AddItem({"Old Item", 1});

    assigned_loot = original_loot;
    assigned_loot.DisplayItems();

    std::cout << "\n\n=== MOVE CONSTRUCTOR ===\n";

    LootContainer moved_loot(std::move(copied_loot));

    std::cout << "Moved-to container:\n";
    moved_loot.DisplayItems();

    std::cout << "\n\nMoved-from container:\n";
    copied_loot.DisplayItems();

    std::cout << "\n\n=== MOVE ASSIGNMENT ===\n";

    LootContainer move_assigned_loot(2);
    move_assigned_loot.AddItem({"Wooden Shield", 15});

    move_assigned_loot = std::move(assigned_loot);

    std::cout << "Move-assigned container:\n";
    move_assigned_loot.DisplayItems();

    std::cout << "\n\nMoved-from assigned container:\n";
    assigned_loot.DisplayItems();

    std::cout << "\n\n=== INVALID CAPACITY TEST ===\n";

    LootContainer invalid_loot(-5);

    bool invalid_add = invalid_loot.AddItem({"Impossible Item", 999});

    if(!invalid_add)
    {
        std::cout << "Could not add item to invalid container.\n";
    }

    invalid_loot.DisplayItems();

    std::cout << '\n';

    return 0;
}
