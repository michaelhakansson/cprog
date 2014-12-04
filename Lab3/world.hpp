#ifndef WORLD_H
#define WORLD_H

#include "environment.hpp" // OBS! Uncommenting this line generates 'duplicate symbol' error on compilation
#include "character.hpp"

class World {
private:
    std::vector<Environment *> environments_;
    Character * main_character_;
    Environment * starting_environment_;
public:
	void init();
};


#endif // WORLD_H