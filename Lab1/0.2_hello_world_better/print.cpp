#include <iostream>
#include <cstdlib>

void printStuff(int argc, char *argv[]) {
	switch(argc) {
		case 1:
			std::cout << "Hello, world!" << std::endl;
			break;
		case 2:
			std::cout << "Hello, " << argv[1] << "!" << std::endl;
			break;
		case 3:
		{
			int numberOfRepeats = std::atoi(argv[2]);
			if(numberOfRepeats <= 0) {
				std::cerr << "error: 2nd argument must be an integral greater than zero!" << std::endl;
			} else {
				std::cout << "Hello,";
				for (int i = 0; i < numberOfRepeats; ++i)
					std::cout << " " << argv[1];
				std::cout << "!" << std::endl; 
			}
			break;
		}
		default:
			std::cerr << "error: Too many arguments!" << std::endl;
	}
}