#include "world.hpp"

// Generates a collection of environments and characters etc
void World::init() {

	// Generate map
    starting_environment_ = new Environment();
    //environments_.push_back(starting_environment_);

	// Place characters inside maps
    main_character_ = new Character();
    //main_character_->enter(starting_environment_);
}
