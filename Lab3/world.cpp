#include "world.hpp"

// Generates a collection of environments and characters etc
void World::init() {

	// Generate map
    starting_environment_ = new Environment();
    environments_.push_back(starting_environment_);

	// Place characters inside maps
    main_character_ = new Character("Robot", "TestBot", 10, 10, "SEGFAULT", starting_environment_);
}

void World::description(){
    std::cout << main_character_->get_environment()->description() << std::endl;
}
