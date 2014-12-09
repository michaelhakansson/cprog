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
	    Character * main_character_;
	    Environment * starting_environment_;
	public:
		void init();
	    bool description(std::string);
	    bool move_character(std::string);
	};

}

#endif // WORLD_H
