#include "world.hpp"

namespace jonsson_league {

	// Generates a collection of environments and characters etc
	void World::init() {
		
		// Declare all the environments in the world
		Environment * entrance = new Environment("A very dark room, you hear the faint sounds of nerds typing.", "Default");
		// TODO: More environments

		entrance->set_neighbour(NORTH, entrance);
		entrance->set_neighbour(SOUTH, entrance);

		// Declare all the items in the world
		Item * sword = new Item("Svärdet Sivert", 1, 1);
		Item * pants = new Item("Byxan Bosse", 1, 1);

		// TODO: More items
		// TODO: Put items in vectors per room
		std::vector<Item*> items_room_0;
		items_room_0.push_back(sword);
		items_room_0.push_back(pants);

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
	    std::cout << current_environment->description() << std::endl;

	    if (current_environment->items()->size()) {
	    	std::cout << "In this room the following item(s) can be seen: "
	    		  << current_environment->item_string()
	    		  << std::endl;
	    }

		return true;
	}

	bool World::move_character(std::string input_direction){
		direction_t direction;

		// Make input upper case to remove case sensitivity
		transform(input_direction.begin(), input_direction.end(), input_direction.begin(), toupper);
		
		//If the argument is valid
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
			std::cout << "invalid direction" << std::endl;
			return false;
		} else {

			//If it's possible to enter in that direction
			if(main_character_->get_environment()->get_neighbour(direction)){
				main_character_ -> go(direction);
				return true;
			} else {
				std::cout << "didn't find any direction" << std::endl;
				return false;
			}
		}

		return true;
	}

	bool World::directions(std::string args){
		std::cout << "You can go:" << std::endl;
		for (int i = 0; i < 4; ++i) {
			if (main_character_->get_environment()->get_neighbour(i)) {
				std::cout << get_string_from_enum(i) << std::endl;
			}
		}
		return true;
	}

	std::string World::get_string_from_enum(int num) {
	  switch (num) {
	  case 0: return "north";
	  case 1: return "west";
	  case 2: return "south";
	  case 3: return "east";
	  default: return "nowhere";
	  }
	}

}
