#include <iostream>
#include "world.hpp"
#include <map>
#include <algorithm>

bool input();
std::string splice_function(std::string);
std::string splice_arguments(std::string);

// TODO namespace for everything
int main(int argc, char* argv[]) {
    
	World * world = new World();
	world->init();

	std::map<std::string, void (World::*)(std::string)> functions;
	functions["description"] = &World::description;
	functions["go"] = &World::move_character;

    // This is the main loop of the game, it handles everything
	while(true) {

		std::string input;
		std::cout << "> ";
		std::getline(std::cin, input);

		if(functions[splice_function(input)] != NULL){
			(world->*(functions[splice_function(input)]))(splice_arguments(input));
		}
	}

    return 1;
}

//Returns the first word of a string
std::string splice_function(std::string str) {
	std::size_t val = str.find(" "); // Finds the first whitespace
	return str.substr(0, std::min(val, str.length()));
}

//Returns all the words in the string except for the first
std::string splice_arguments(std::string str) {
	std::size_t val = str.find(" ");
	return str.substr(std::min(val + 1, str.length()), str.length());
}