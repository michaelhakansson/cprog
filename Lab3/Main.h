#include <iostream>
#include "World.h"

//TODO the resolution of the window in pixels
static final int WIDTH = 400;
static final int HEIGHT = 300;

//TODO namespace for everything
void main(int argc, char* argv[]) {
    
	World world = new World();
	world.init();

	Renderer renderer = new Renderer();

    //This is the main loop of the game, it handles everything
	while(true) {

		//Gets user input
		input();

		//Updates the model
		world.update();

		//Renders the model graphically
		renderer.render(world);

		//Sleep so that we don't exceed 30FPS and set fire to some poor CPU
	}

    return;
}
