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
		Character * spider = new Character("Spider", "Imse Vimse", 20, 1, "bites", boss_room);
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
		// check_status (hälsa etc.)
		// resolve next character
		// 
		// Main characters turn
		
		// The attack
		Character * attacker = get_current_character();
		Character * target = get_target(args);
		std::cout << attacker->get_name() << " " << attacker->get_name_of_attack() << " " << target->get_name() << " for " << attacker->get_strength() << " damage" << std::endl;

		// Update HP of target
		target->set_health(target->get_health() - attacker->get_strength());

		set_current_character(get_next_character());

		check_status();

		return true;
	}

	void World::check_status() {
	
		std::vector<Character*> enemies = get_local_enemies();
		for (int i = 0; i < (int) enemies.size(); ++i) {
			if (!enemies[i]->is_dead()) {
				return;
			}
		}

		std::cout << "You have defeated the enemy!" << std::endl;
	
		set_combat_flag(false);
	}

	Character* World::get_target(std::string target) {
		// Main characters turn
		// TODO: get target by name
		if (get_current_character() == get_main_character()) {
			std::vector<Character*> enemies = get_local_enemies();
			for (int i = 0; i < (int) enemies.size(); ++i) {
				if (!enemies[i]->is_dead()) {
					return enemies[i];
				}
			}	
		} else { // Enemies turn
			return get_main_character();
		}
		return NULL;
	}

	Character* World::get_target_by_name(std::string target) const {
		
		//If we have empty string
		if(target == ""){
			return NULL;
		}

		std::string name;
		std::vector<Character*> enemies = get_local_enemies();

		for (int i = 0; i < (int) enemies.size(); ++i) {
			
			name = enemies.at(i)->get_name();
			transform(name.begin(), name.end(), name.begin(), toupper);

			if(target == name){
				return enemies.at(i);
			}
		}	

		return NULL;
	}

	Character* World::get_next_character() const {

		std::vector<Character*> enemies = get_local_enemies();

		//If the current character is the main character
		if (get_current_character() == get_main_character()) {
			for (int i = 0; i < (int) enemies.size(); ++i) {
				if (enemies[i]->get_health() > 0) {
					return enemies[i];
				}
			}	
			return get_main_character();
		} 
		//If we have the enemy
		else {
			//Gets the index of the current enemy
			int pos = find(enemies.begin(), enemies.end(), get_current_character()) - enemies.begin();

			//If we can iterate to the next enemy
			if(pos + 1 < (int) enemies.size()){
				return enemies.at(pos + 1);
			} 

			//Otherwise, it's the main characters turn
			else {
				return get_main_character();
			}
		}
		return NULL;
	}

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
		set_local_enemies(&local_enemies_);

		for(int i = 0; i < (int) local_enemies_.size(); i++){

			if(local_enemies_.at(i)->get_environment() == main_character_->get_environment() && (aggressive || local_enemies_.at(i)->get_aggression())){
				set_combat_flag(true);
				combat_initated = true;

				std::cout << "You enter combat with " << local_enemies_.at(i)->get_name() << std::endl;
			}
		}

		return combat_initated;
	}

	std::vector<Character *> World::get_local_enemies() const {
		return local_enemies_;
	}

	//Gets all the enemies in the same environment as the main character
	void World::set_local_enemies(std::vector<Character *> * vec) {

		vec->clear();

		for(int i = 0; i < (int) enemies_.size(); i++){

			if(enemies_.at(i)->get_environment() == get_main_character()->get_environment() && enemies_.at(i) != get_main_character() && !enemies_.at(i)->is_dead()){
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

	Character* World::get_main_character() const {
		return main_character_;
	}

	void World::set_main_character(Character * character) {
		main_character_ = character;
	}

	Character* World::get_current_character() const {
		return current_character_;
	}

	void World::set_current_character(Character * character) {
		current_character_ = character;
	}
}
