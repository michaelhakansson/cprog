#include "world.hpp"

// Generates a collection of environments and characters etc
void World::init() {
	// Declare all the items in the world
	// TODO: More items
	// TODO: Put items in vectors per room
	std::vector<Item> items_room_0;

	// Declare all the environments in the world
	Environment * entrance = new Environment(items_room_0, neighbors_room_0, "Room 0", "room");
	// TODO: More environments

	// TODO: Declare all links between rooms
	std::vector<Environment> neighbors_room_0;
	// TODO: More links

	// TODO: Put all environments in vector
    environments_.push_back(starting_environment_);
    // TODO: Push more elements

	// Generate map
    starting_environment_ = entrance;
    // TODO: Link environments

	// Place characters inside maps
    main_character_ = new Character("Robot", "TestBot", 10, 10, "SEGFAULT", starting_environment_);
}

void World::description(std::string args){
    std::cout << main_character_->name()
    		  << " is in "
    		  << main_character_->get_environment()->description() 
    		  << std::endl;
}

void World::move_character(std::string input_direction){
	direction_t direction;

	// Make input upper case to remove case sensitivity
	transform(input_direction.begin(), input_direction.end(), input_direction.begin(), toupper);
	
	if (input_direction == "NORTH") {
		direction = NORTH;
	} else if (input_direction == "WEST") {
		direction = WEST;
	} else if (input_direction == "SOUTH") {
		direction = SOUTH;
	} else if (input_direction == "east") {
		direction = EAST;
	} else {
		direction = INVALID;
	}
	if (direction == INVALID) {
		// TODO: ERROR HANDLING
	} else {
		main_character_ -> go(direction);
	}

}
