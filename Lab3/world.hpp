#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <algorithm>
#include "environment.hpp"
#include "character.hpp"
#include "directions.hpp"

namespace jonsson_league {

	class World {
	private:
	    std::vector<Environment *> environments_;
	    Environment * starting_environment_;
	    std::vector<Character *> enemies_;
	    Character * main_character_;
	    bool in_combat_;
	    bool main_character_turn_;
	public:
		void init();
		void describe_room();
	    bool description(std::string);
	    bool move_character(std::string);
	    bool directions(std::string args);
	    bool attack(std::string args);
	    bool in_combat();
	    bool set_combat_flag(bool);
	    bool resolve_combat(bool aggressive);

	    std::string get_string_from_enum(int num);
	};

}

#endif // WORLD_H
