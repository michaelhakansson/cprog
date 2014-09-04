#include <iostream>
#include <cstdlib>
#include "translation.h"

int main(int argc, char *argv[]){
	
	char * name = NULL;
	int number = 1;

	if(argc >= 2){
		name = argv[1];
	}

	if(argc >= 3){
		number = std::atoi(argv[2]);
	}

	if(argc > 3){
		std::cerr << "error: Too many arguments!\n";
		return 1;
	}

	translation(name, number);
	return 0;
}
