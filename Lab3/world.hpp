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
	public:
		void init();
		void describe_room();
	    bool description(std::string);
	    bool move_character(std::string);
	    bool directions(std::string args);
	    std::string get_string_from_enum(int num);
	    bool in_combat();
	};

}

#endif // WORLD_H
