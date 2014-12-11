#include <iostream>
#include <fstream>
#include "world.hpp"
#include <map>
#include <algorithm>


bool input();
std::string splice_function(std::string);
std::string splice_arguments(std::string);
void print_file(std::string);

int main(int argc, char* argv[]) {

	print_file("intro.txt");
	//print_file("tutorial.txt");
    
	jonsson_league::World * world = new jonsson_league::World();
	world->init();

	//Maps commands to functions
	std::map<std::string, bool (jonsson_league::World::*)(std::string)> functions;
	functions["DESCRIPTION"] = &jonsson_league::World::description;
	functions["DESCRIPTIONS"] = &jonsson_league::World::description;
	functions["DESCRIBE"] = &jonsson_league::World::description;

	functions["GO"] = &jonsson_league::World::move_character;
	functions["MOVE"] = &jonsson_league::World::move_character;
	functions["WALK"] = &jonsson_league::World::move_character;
	
	functions["DIRECTION"] = &jonsson_league::World::directions;
	functions["DIRECTIONS"] = &jonsson_league::World::directions;
	
	functions["SUICIDE"] = &jonsson_league::World::suicide;
	//functions["INVESTIGATE"] = &jonsson_league::World::investigate;
	//TODO attack?

	//For combat, we restrict the player to a different set of functions
	std::map<std::string, bool (jonsson_league::World::*)(std::string)> combat_functions;
	combat_functions["ATTACK"] = &jonsson_league::World::attack;
	//TODO special?

    // This is the main loop of the game, it handles everything
	while(true) {

		std::string input;
		std::cout << world->get_current_character()->get_name() << "> ";
		std::getline(std::cin, input);

		//Input to upper case
		transform(input.begin(), input.end(), input.begin(), toupper);

		//The player wants to exit
		if(splice_function(input) == "EXIT" || splice_function(input) == "QUIT"){
			return 1;
		}

		//If we aren't in combat
		if(!world->in_combat()){

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

		//If we are in combat
		else {
			
			//Check if the desired function is in the map
			if(combat_functions[splice_function(input)] != NULL){

				//Run the function and check if it successfully completed
				if(!(world->*(combat_functions[splice_function(input)]))(splice_arguments(input))){
					std::cout << "Invalid arguments!" << std::endl;
				}
			} else {
				std::cout << "Invalid command!" << std::endl;
			}
		}

		//If the player has died
		if(world->get_main_character()->get_health() <= 0){
			print_file("game_over.txt");

			return 1;
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

//Takes a file name and prints out an arbitrary file
void print_file(std::string filename){
	std::string line;
	std::ifstream file (filename);
	
	if (file.is_open()){
		
		while(getline(file, line) ){
			std::cout << line << '\n';
		}

		file.close();
	}

	return;
}
