#include "Loot.h"

LootContainer::LootContainer(int capacity) :
    m_capacity{capacity},
    m_item_count{0}
{
    if(capacity <= 0)
    {
        m_items = nullptr;
        m_capacity = 0;
    }
    else
        m_items = new LootItem[capacity];

}

LootContainer::LootContainer(const LootContainer& other) :
    m_capacity{other.m_capacity},
    m_item_count{other.m_item_count}
{
    m_items = new LootItem[m_capacity];
    
    for(int i = 0; i < other.m_item_count; i++)
    {
        m_items[i] = other.m_items[i];
    }

}

LootContainer::LootContainer(LootContainer&& other) noexcept :
    m_capacity{other.m_capacity},
    m_item_count{other.m_item_count},
    m_items{other.m_items}
{
    other.m_items = nullptr;
    other.m_capacity = 0;
    other.m_item_count = 0;
}


LootContainer& LootContainer::operator=(const LootContainer& other)
{
    if(this == &other)
        return *this;
    
    // Allocate new LootItem array and set it's size to other.m_capacity
    LootItem* new_items = new LootItem[other.m_capacity];

    // Then copy from other.m_items into new_items array
    for(int i = 0; i < other.m_item_count; i++)
        new_items[i] = other.m_items[i];

    delete[] m_items;

    m_items = new_items;
    m_item_count = other.m_item_count;
    m_capacity = other.m_capacity;
    return *this;
}

LootContainer& LootContainer::operator=(LootContainer&& other) noexcept
{
    if(this == &other)
    {
        return *this;
    }

    delete[] m_items;

    m_capacity = other.m_capacity;
    m_item_count = other.m_item_count;
    m_items = other.m_items;

    other.m_items = nullptr;
    other.m_item_count = 0;
    other.m_capacity = 0;
    return *this;
}

LootContainer::~LootContainer()
{
    delete[] m_items;
}

bool LootContainer::AddItem(const LootItem& new_item)
{
    if(m_item_count + 1 > m_capacity)
    {
        return false;
    }

    m_items[m_item_count] = new_item;

    ++m_item_count;
    return true;
}

bool LootContainer::RemoveItem(int item_index, LootItem& removed_item)
{
    if(item_index >= m_item_count || item_index < 0)
        return false;
    
    removed_item = m_items[item_index];

    for(int i = m_item_count - 1; i > item_index; --i)
    {
        m_items[i - 1] = m_items[i];
    }
    
    --m_item_count;
    return true;
}

bool LootContainer::TransferItem(int item_index, LootContainer& destination)
{    
    if(item_index >= m_item_count 
            || item_index < 0
            || destination.m_item_count + 1 > destination.m_capacity
            || this == &destination)
        return false;
    
    LootItem source_item = m_items[item_index];

    if(!(destination.AddItem(source_item)))
        return false;

    if(!RemoveItem(item_index, source_item))
        return false;

    return true;
}

void LootContainer::DisplayItems() const
{
    std::cout << '\n';

    for(int i = 0; i < 25; i++)
    {
        std::cout << "=";
    }

    std::cout << "\n\tINVENTORY\n";

    for(int i = 0; i < m_item_count; i++)
    {
        std::cout << i << ". " << m_items[i].item_name << '\n';
    }

    std::cout << '\n';

    for(int i = 0; i < 25; i++)
    {
        std::cout << "=";
    }
}
