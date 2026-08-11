#pragma once
#include <iostream>
#include <string>

struct LootItem
{
    std::string item_name;
    int gold_value;
};

class LootContainer
{
    public:
        LootContainer(int capacity);
        LootContainer(const LootContainer& other);
        LootContainer(LootContainer&& other) noexcept;

        LootContainer& operator=(const LootContainer& other);
        LootContainer& operator=(LootContainer&& other) noexcept;

        ~LootContainer();

        bool AddItem(const LootItem& new_item);
        bool RemoveItem(int item_index, LootItem& removed_item);
        bool TransferItem(int item_index, LootContainer& destination);
        void DisplayItems() const;

    private:
        int m_capacity;
        int m_item_count;
        LootItem* m_items;
};
