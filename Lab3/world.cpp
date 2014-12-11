#include "world.hpp"

namespace jonsson_league {

	// Generates a collection of environments and characters etc
	void World::init() {
		
		// Declare all the environments in the world
		Environment * entrance = new Environment("A very dark room, you hear the faint sounds of nerds typing.", "Default");
		// TODO: More environments

		// Declare all the items in the world
		Item * sword = new Item("Svärdet Sivert", "A legendary sword, forged by blacksmith Yggrimmar.", 1, 1);
		Item * pants = new Item("Byxan Bosse", "A legendary pair of pants, forged by children in Indonesia.", 1, 1);

		// TODO: More items
		// TODO: Put items in vectors per room
		entrance->set_item(sword);
		entrance->set_item(pants);

		// TODO: Put all environments in vector
	    environments_.push_back(starting_environment_);
	    // TODO: Push more elements
		
		// Generate map
	    starting_environment_ = entrance;
	    // TODO: Link environments		

		// Place characters inside maps
	    main_character_ = new Character("Robot", "TestBot", 10, 10, "SEGFAULT", starting_environment_);
	    current_character_ = main_character_;

		Environment * boss_room = new Environment("A room filled with spider webs, you hear crawling in the corner", "Boss room");
		Character * spider = new Character("Spider", "Imse Vimse", 1, 1, "bites", boss_room);
		spider->set_aggression(true);
		enemies_.push_back(spider);

		entrance->set_neighbour(NORTH, boss_room);
		boss_room->set_neighbour(SOUTH, entrance);
	}

	void World::describe_room() {
		Environment * current_environment = main_character_->get_environment();
	    std::cout << current_environment->get_description() << std::endl;

	    if (current_environment->get_items()->size()) {
	    	std::cout << "In this room the following item(s) can be seen: " << std::endl;

			for(int i = 0; i < (int) current_environment->get_items()->size(); ++i){
				std::cout << (* (current_environment->get_items()))[i]->get_name() << ", \"" << (* (current_environment->get_items()))[i]->get_description() << "\"" << std::endl;
			}
	    }
	}

	bool World::description(std::string args){
		describe_room();
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
				std::cout << "Character " << main_character_->get_name() << " goes " << get_string_from_enum(direction) << "." << std::endl;
				describe_room();
				resolve_combat(false);

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

	bool World::attack(std::string args){

		if(current_character_ == main_character_){

			//Check if dead
			current_character_ = local_enemies_[0];

			//get character by name

		} else {

			if(current_character_ == local_enemies_[local_enemies_.size()]){
				current_character_ = main_character_;
			}

			std::cout << "Player takes 1 damage!" << std::endl;

		}

		//if combat ends

		return true;
	}

	//get_characters_by_name

	bool World::in_combat(){
		return in_combat_;
	}

	bool World::set_combat_flag(bool combat){
		in_combat_ = combat;

		//Sets the main characters turn when we both enter and leave combat
		current_character_ = main_character_;
		
		if(false){
			local_enemies_.clear();
		}

		return true;
	}

	//Checks whether combat will occurr
	//If the aggressive flag is set, combat will always be
	bool World::resolve_combat(bool aggressive){

		bool combat_initated = false;
		get_local_enemies(&local_enemies_);

		for(int i = 0; i < (int) local_enemies_.size(); i++){

			if(local_enemies_.at(i)->get_environment() == main_character_->get_environment() && (aggressive || local_enemies_.at(i)->get_aggression())){
				set_combat_flag(true);
				combat_initated = true;

				std::cout << "You enter combat with " << local_enemies_.at(i)->get_name() << std::endl;
			}
		}

		return combat_initated;
	}

	//Gets all the enemies in the same environment as the main character
	void World::get_local_enemies(std::vector<Character *> * vec){

		for(int i = 0; i < (int) enemies_.size(); i++){

			if(enemies_.at(i)->get_environment() == main_character_->get_environment()){
				vec->push_back(enemies_.at(i));
			}
		}
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
