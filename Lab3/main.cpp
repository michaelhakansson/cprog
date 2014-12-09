#include <iostream>
#include <fstream>
#include "world.hpp"
#include <map>
#include <algorithm>


bool input();
std::string splice_function(std::string);
std::string splice_arguments(std::string);
void print_intro();

// TODO namespace for everything
int main(int argc, char* argv[]) {

	print_intro();
    
	jonsson_league::World * world = new jonsson_league::World();
	world->init();

	std::map<std::string, bool (jonsson_league::World::*)(std::string)> functions;
	functions["DESCRIPTION"] = &jonsson_league::World::description;
	functions["GO"] = &jonsson_league::World::move_character;
	functions["DIRECTIONS"] = &jonsson_league::World::directions;

    // This is the main loop of the game, it handles everything
	while(true) {

		std::string input;
		std::cout << "> ";
		std::getline(std::cin, input);

		//Input to upper case
		transform(input.begin(), input.end(), input.begin(), toupper);

		//Check if the desired function is in the map
		if(functions[splice_function(input)] != NULL){

			//Run the function and check if it successfully completed
			if(!(world->*(functions[splice_function(input)]))(splice_arguments(input))){
				std::cout << "Invalid arguments!" << std::endl;
			}
		} else {
			std::cout << "Invalid command!" << std::endl;
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

void print_intro(){
	std::string line;
	std::ifstream intro_file ("intro.txt");
	
	if (intro_file.is_open()){
		
		while(getline(intro_file, line) ){
			std::cout << line << '\n';
		}

		intro_file.close();
	}

	return;
}
