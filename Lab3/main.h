#include <iostream>
#include "world.h"


// TODO namespace for everything
int main(int argc, char* argv[]) {
    
	World * world = new World();
	world->init();

    // This is the main loop of the game, it handles everything
	// while(true) {

	// 	// Gets user input
	// 	input();

	// 	// Updates the model
	// 	world.update();

	// 	// Renders the model graphically
	// 	renderer.render(world);

	// 	// Sleep so that we don't exceed 30FPS and set fire to some poor CPU
	// }

    return 1;
}
