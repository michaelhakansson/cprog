// projektlokala headerfiler
#include "inventory.hpp"

// STL headerfiler
#include <iostream>
#include <sstream>              // std::stringstream
#include <assert.h>             // assert(b) ger felmeddelande om b falsk


int main()
{
using namespace jonsson_league;        // Exponera funktionalitet i namnrymden lab2

std::cout << "----------------------------------------" << std::endl;
std::cout << "Initiating tests" << std::endl;

{
    std::cout << "Testing default constructor" << std::endl;
    Inventory inventory;
    assert(inventory.get_slot_limit() == 1);
    assert(inventory.get_weight_limit() == 1);
}

{
    std::cout << "Testing (int num_slots, int max_weight) constructor" << std::endl;
    Inventory inventory(3,4);
    assert(inventory.get_slot_limit() == 3);
    assert(inventory.get_weight_limit() == 4);
}

{
    std::cout << "Testing get_number_of_items" << std::endl;
    Inventory inventory;
    assert(inventory.get_number_of_items() == 0);
}

{
    std::cout << "Testing get_weight" << std::endl;
    Inventory inventory;
    assert(inventory.get_weight() == 0);
}

{
    std::cout << "Testing get_slot_limit" << std::endl;
    Inventory inventory;
    assert(inventory.get_slot_limit() == 1);
}

{
    std::cout << "Testing get_weight_limit" << std::endl;
    Inventory inventory;
    assert(inventory.get_weight_limit() == 1);
}

{
    std::cout << "Testing add_item" << std::endl;
    Inventory inventory(2,2);
    Item* item = new Item("It1", "An item1", 1, 1);
    Item* item2 = new Item("It2", "An item2", 1, 1);
    Item* item3 = new Item("It3", "An item3", 1, 1);
    assert(inventory.get_number_of_items() == 0);
    assert(inventory.add_item(item) == true);
    assert(inventory.get_number_of_items() == 1);
    assert(inventory.add_item(item2) == true);
    assert(inventory.get_number_of_items() == 2);
    // Inventory full - should not add new item
    assert(inventory.add_item(item3) == false);
    assert(inventory.get_number_of_items() == 2);
}

{
    std::cout << "Testing get_items" << std::endl;
    Inventory inventory(2,2);
    Item* item = new Item("It1", "An item1", 1, 1);
    Item* item2 = new Item("It2", "An item2", 1, 1);
    assert(inventory.get_number_of_items() == 0);
    assert(inventory.add_item(item) == true);
    assert(inventory.get_number_of_items() == 1);
    assert(inventory.add_item(item2) == true);
    assert(inventory.get_number_of_items() == 2);

    std::vector<Item*> * items = inventory.get_items();
    assert(items->at(0)->get_name() == "It1");
    assert(items->at(1)->get_name() == "It2");
}

std::cout << "All tests passed!" << std::endl;
std::cout << "----------------------------------------" << std::endl;

return 0;
}

