#include "world.hpp"

namespace jonsson_league {

	// Generates a collection of environments and characters etc
	void World::init() {

		// Declare all the environments in the world
		
		Environment * end_state = new Environment("Congratulations!", "End state");

		Environment * entrance = new Environment("A very elegant room, there is a painting showing the monarch covered in expensive jewelry.", "Entrance");
		starting_environment_ = entrance;
		environment_map_["Entrance"] = entrance;

		//Go here to end the game
		entrance->set_neighbour(SOUTH, end_state);

		// Place characters inside maps
	    main_character_ = new Character("Thief", "Jonsson", 10, 10, "slaps", starting_environment_);
		main_character_->set_base_weight(75);
	    current_character_ = main_character_;

		/*
		 * Add all the environments
		 */

		Environment * spider_room = new Environment("A room filled with spider webs... Icky!", "Spider room");
		Character * spider = new Character("Spider", "Imse Vimse", 20, 1, "bites", spider_room);
		spider->set_aggression(true);
		enemies_.push_back(spider);
		environment_map_["Spider room"] = spider_room;

		//Character * spider2 = new Character("Spider", "Vimse Imse", 1, 20, 1, "bites", spider_room);
		//spider2->set_aggression(true);
		//enemies_.push_back(spider2);

		spider_room->set_neighbour(SOUTH, entrance);
		entrance->set_neighbour(NORTH, spider_room);

		Environment * dining_room = new Environment("A dining room filled with delicious food! Maybe you should EAT some?", "Dining room");
		environment_map_["Dining room"] = dining_room;
		
		dining_room->set_neighbour(SOUTH, spider_room);
		spider_room->set_neighbour(NORTH, dining_room);
		
		Environment * kandelaber_room = new Environment("A room with a terribly unfashionable kandelaber. It's so unfashionable it makes you want to KICK it...", "Kandelaber room");
		environment_map_["Kandelaber room"] = kandelaber_room;
		kandelaber_room->set_neighbour(WEST, dining_room);
		dining_room->set_neighbour(EAST, kandelaber_room);

		//TODO catacombs

		Environment * fuskbygge = new Environment("A fuskbygge that is almost falling apart! Damn polish immigrants!", "Fuskbygge");
		environment_map_["Fuskbygge"] = fuskbygge;
		fuskbygge->set_neighbour(NORTH, kandelaber_room);
		kandelaber_room->set_neighbour(SOUTH, fuskbygge);

		Environment * princess_room = new Environment("A room with the faint glow of glow of computer screens. Victoria and Madeleine are LANing rock paper scissors!", "Princess room");
		environment_map_["Princess room"] = princess_room;
		princess_room->set_neighbour(NORTH, fuskbygge);
		fuskbygge->set_neighbour(SOUTH, princess_room);

		Environment * bedroom = new Environment("The royal bedrooom, with a sleeping queen Silvia!", "Bedroom");	
		environment_map_["Bedroom"] = bedroom;
		bedroom->set_neighbour(WEST, princess_room);
		princess_room->set_neighbour(EAST, bedroom);

		Character * silvia = new Character("Queen", "Silvia", 20, 3, "shrieks", bedroom);
		silvia->set_aggression(false);
		enemies_.push_back(silvia);

		Environment * trophy_room = new Environment("A trophy room. Filled with the skulls of thieves who have tried to steal from the one true monarch...", "Trophy room");
		environment_map_["Trophy room"] = trophy_room;
		trophy_room->set_neighbour(SOUTH, bedroom);
		bedroom->set_neighbour(NORTH, trophy_room);

		//TODO restrict access to throne room
		Environment * throne_room = new Environment("The throne room... full with all kinds of treasures and jewels! And a sleeping monarch...", "Throne room");
		environment_map_["Throne room"] = throne_room;
		throne_room->set_neighbour(WEST, kandelaber_room);
		kandelaber_room->set_neighbour(EAST, throne_room);
		
		Character * kungen = new Character("King", "Carl XVI Gustav", 50, 5, "fires the royal älgbössa at", throne_room);
		kungen->set_aggression(false);
		enemies_.push_back(kungen);
		
		throne_room->set_neighbour(SOUTH, trophy_room);
		trophy_room->set_neighbour(NORTH, throne_room);

		character_map_["MAIN"] = main_character_;
		character_map_["IMSE VIMSE"] = spider;
		character_map_["SILVIA"] = silvia;
		character_map_["KUNGEN"] = kungen;
		//character_map_["VIMSE IMSE"] = spider2;
		
		// Declare all the items in the world
		Item * toffel_of_silence = new Item("Toffel of silence", "A unisex toffel that makes it's wearer move extremely silent.", 1, 10, 2, 0);

		// TODO: More items
		spider_room->add_item(toffel_of_silence);

	}

	void World::print_items(std::vector<Item*> * vec) const {
		if ((*vec)[0] == NULL) { 
			std::cout << "NULL!" << std::endl;
		}
		for(int i = 0; i < (int) vec->size(); ++i) {
			std::cout << "* " << (*vec)[i]->get_name() << ", \"" << (*vec)[i]->get_description() << "\"" << std::endl;
		}
	}

	//Describes the room, and the items in it
	void World::describe_room() const {
		Environment * current_environment = main_character_->get_environment();
	    std::cout << current_environment->get_description() << std::endl;

	    if (current_environment->get_container()->get_number_of_items()) {
	    	std::cout << "In this room you see the following item(s): " << std::endl;
	    	print_items(current_environment->get_container()->get_items());
	    }
	}

	//Prints the inventory of the current character
	bool World::describe_inventory(std::string args) {
		print_items(get_main_character()->get_inventory()->get_items());
		return true;
	}

	//Prints status for current character
	bool World::player_status(std::string args) {
		Character* character = get_current_character();
		std::cout << "Status for " << character->get_name() << std::endl;
		std::cout << "Health: " << character->get_health() << "/" << character->get_max_health() << std::endl;
		std::cout << "Strength: " << character->get_strength() << std::endl;
		std::cout << "Weight: " << character->get_weight() <<std::endl;
		std::cout << "Inventory:" << std::endl;
		print_items(character->get_inventory()->get_items());

		return true;
	}

	bool World::description(std::string args){
		describe_room();
		return true;
	}

	//Moves the main character in a direction
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
			std::cout << "invalid direction" << std::endl;
			return false;
		}
		
		std::cout << "Character " << main_character_->get_name() << " goes " << get_string_from_enum(direction) << "." << std::endl;

		//If it's possible to enter in that direction
		if(main_character_->get_environment()->get_neighbour(direction)){

			std::string next_environment_type = get_main_character()->get_environment()->get_neighbour(direction)->get_type();

			//If the character tries to enter the fuskbygge
			if(next_environment_type == "Fuskbygge"){
				
				//If the main character weighs more than a specified amount
				if(get_main_character()->get_weight() >= 80){
					
					//TODO
					std::cout << "Due to yoru weight sdfakj" << std::endl;

					Environment * fuskbygge = environment_map_["Fuskbygge"];

					Environment * catacomb = new Environment("A dark and moist catacomb", "Catacomb");
					catacomb->set_neighbour(NORTH, environment_map_["Kandelaber room"]);
					catacomb->set_neighbour(SOUTH, environment_map_["Princess room"]);
					
					environment_map_["Kandelaber room"]->set_neighbour(SOUTH, catacomb);
					environment_map_["Princess room"]->set_neighbour(NORTH, catacomb);

					//TODO place spy somewhere

					
					//TODO proper destructorsi
					environment_map_["Fuskbygge"] = NULL;
					delete fuskbygge;
				}
			}

			else if(next_environment_type == "Bedroom"){
				
				//TODO check if you have slippers of silence
				character_map_["SILVIA"]->set_aggression(true);
				resolve_combat(true);
			}

			main_character_ -> go(direction);
			describe_room();
			resolve_combat(false);

			return true;
		}

		return false;
	}

	//Prints the directions the character can go
	bool World::directions(std::string args){
		std::cout << "You can go:" << std::endl;
		for (int i = 0; i < 4; ++i) {
			if (main_character_->get_environment()->get_neighbour(i)) {
				std::cout << get_string_from_enum(i) << std::endl;
			}
		}
		return true;
	}

	bool World::take(std::string args){
		Character* character = get_main_character();

		//If you are in the throne room
		if(character->get_environment()->get_type() == "Throne room"){
			float r = (rand()) / (float) (RAND_MAX);

			//If you are unlucky
			if(r <= 0.2){
				std::cout << "The monarch has awoken!" << std::endl;
				character_map_["KUNGEN"]->set_aggression(true);
				resolve_combat(true);
			}
		}

		Item* item;
		if (args == "TAKE") { // No name specified
			if (character->get_environment()->get_container()->get_number_of_items() <= 0) {
				return false;
			}
			// Take first element
			item = character->get_environment()->get_container()->get_items()->at(0);
			character->take(item);
			character->get_environment()->get_container()->remove_item(item);
		} else { // Take item by name
			item = character->get_environment()->get_container()->get_item_by_name(args);
			if (item == NULL) {
				std::cout << "Could not find item " << "\"" << args << "\"" << std::endl;
				return false;
			} else {
				if (!character->take(item)) {
					std::cout << "Could not take up item" << std::endl;
					return false;
				}
			}	
		}
		std::cout << "You took " << item->get_name() << std::endl;
		return true;
	}

	bool World::drop(std::string args) {
		Character* character = get_main_character();

		Item* item = character->get_inventory()->get_item_by_name(args);
		if (args == "DROP") {
			std::cout << "You must specify what you want to drop." << std::endl;
			return false;
		}
		
		if (item == NULL) {
			std::cout << "Could not find item " << "\"" << args << "\"" << std::endl;
			return false;
		} 
		character->drop(item);
		std::cout << "You dropped " << item->get_name() << std::endl;
		return true;
	}

	//Eats food, only available in the dining room
	bool World::eat(std::string args){
		
		if(get_main_character()->get_environment()->get_type() == "Dining room"){

			std::cout << "You eat from the delicious food on the tables." << std::endl;
			
			int health_diff = get_main_character()->get_health() - get_main_character()->get_max_health();
			
			if(health_diff != 0){
				std::cout << "You gain 1 HP." << std::endl;
			}

			get_main_character()->set_health(get_main_character()->get_health() + 1);

			get_main_character()->set_base_weight(get_main_character()->get_base_weight() + 1);

			if(get_main_character()->get_weight() >= 80){
				std::cout << "You feel full. Maybe you shouldn't eat any more..." << std::endl;
			}

			return true;
		}

		return false;
	}

	//If you kick the kandelaber, opens a secret room
	bool World::kick(std::string args){
	
		if(get_main_character()->get_environment()->get_type() == "Kandelaber room"){
			
			std::cout << "You kick the kandelaber, it falls down and a hidden door is revealed!" << std::endl;

			environment_map_["Kandelaber room"]->set_neighbour(EAST, environment_map_["Throne room"]);
			environment_map_["Throne room"]->set_neighbour(WEST, environment_map_["Kandelaber room"]);

			return true;
		}

		return false;
		
	}

	//Attacks an enemy (must be in combat)
	bool World::attack(std::string args){
		// check_status (hälsa etc.)
		// resolve next character
		// 
		// Main characters turn
		
		// The attack
		Character * attacker = get_current_character();
		Character * target = get_target(args);

		// Update HP of target
		target->set_health(target->get_health() - attacker->get_strength());
	
		std::cout << attacker->get_name() << " " << attacker->get_name_of_attack() << " " << target->get_name() << " for " << attacker->get_strength() << " damage" 
			<< " (" << target->get_health() << " remaining)" << std::endl;
		
		if(target->is_dead()){
			std::cout << target->get_name() << " was defeated!" << std::endl;
		}

		set_current_character(get_next_character());

		check_status();

		return true;
	}

	//Kills the main character
	bool World::suicide(std::string args){
		get_main_character()->set_health(0);

		return true;
	}

	//Checks whether combat ends
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

	//Gets target in combat
	Character* World::get_target(std::string target) {
		
		Character * result = get_target_by_name(target);

		//If we get a proper result, return
		if(result != NULL){
			return result;
		}

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

	Character * World::get_character_by_name(std::string target) {
		return character_map_[target];
	}

	//Gets specific target in combat
	Character* World::get_target_by_name(std::string target) {
		
		Character * result = get_character_by_name(target);
		
		//If we have empty string
		if(result == NULL){
			return NULL;
		}

		if(std::find(get_local_enemies().begin(), get_local_enemies().end(), result) != get_local_enemies().end()) {
			return result;
		}

		return NULL;
	}

	//Resolves the next character in combat
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
			for(int i = pos + 1; i < (int) enemies.size(); i++){
				if(!enemies[i]->is_dead()){
					return enemies[i];
				}
			} 

			//Otherwise, it's the main characters turn
			return get_main_character();
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
