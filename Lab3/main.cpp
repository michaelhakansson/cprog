#include <iostream>
#include "world.hpp"

bool input();

// TODO namespace for everything
int main(int argc, char* argv[]) {
    
	World * world = new World();
	world->init();

    // This is the main loop of the game, it handles everything
	while(true) {

		std::string input;
		std::cout << "> ";
		std::cin >> input;

		//result = input bla bla map

		if(input == "description"){

			world->description();

		// 	// Updates the model
		// 	world.update();

		// 	// Renders the model graphically
		// 	renderer.render(world);

		// 	// Sleep so that we don't exceed 30FPS and set fire to some poor CPU
		// 

		}
	}

    return 1;
}
