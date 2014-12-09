#include "world.hpp"

// Generates a collection of environments and characters etc
void World::init() {
	// Declare all the items in the world
	Item * sword = new Item("Svärdet Sivert", 1, 1);
	Item * pants = new Item("Byxan Bosse", 1, 1);

	// TODO: More items
	// TODO: Put items in vectors per room
	std::vector<Item*> items_room_0;
	items_room_0.push_back(sword);
	items_room_0.push_back(pants);

	// TODO: Declare all links between rooms
	std::vector<Environment> neighbors_room_0;
	// TODO: More links

	// Declare all the environments in the world
	Environment * entrance = new Environment(items_room_0, neighbors_room_0, "Room 0", "room");
	// TODO: More environments


	// TODO: Put all environments in vector
    environments_.push_back(starting_environment_);
    // TODO: Push more elements

	// Generate map
    starting_environment_ = entrance;
    // TODO: Link environments

	// Place characters inside maps
    main_character_ = new Character("Robot", "TestBot", 10, 10, "SEGFAULT", starting_environment_);
}

bool World::description(std::string args){
	Environment * current_environment = main_character_->get_environment();
    std::cout << main_character_->name()
    		  << " is in "
    		  << current_environment->description() 
    		  << std::endl;
    if (current_environment->items().size()) {
    	std::cout << "In this "
    		  << current_environment->type()
    		  << " the following item(s) can be seen: "
    		  << current_environment->item_string()
    		  << std::endl;
    }

	return true;
}

bool World::move_character(std::string input_direction){
	direction_t direction;

	// Make input upper case to remove case sensitivity
	transform(input_direction.begin(), input_direction.end(), input_direction.begin(), toupper);
	
	if (input_direction == "NORTH") {
		direction = NORTH;
	} else if (input_direction == "WEST") {
		direction = WEST;
	} else if (input_direction == "SOUTH") {
		direction = SOUTH;
	} else if (input_direction == "EAST") {
		direction = EAST;
	} else {
		direction = INVALID;
	}
	if (direction == INVALID) {
		return false;
	} else {
		main_character_ -> go(direction);
	}

	return true;
}
