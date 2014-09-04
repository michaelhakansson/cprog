#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[]){

  //If we have more than 2 arguments
  if(argc > 3){
    std::cerr << "error: Too many arguments!\n";
	return 1;
  }

  //If we have a name
  else if(argc == 2){
    std::cout << "Hello, " << argv[1] << "!\n"; 
  }

  else if(argc == 3){
    if(std::atoi(argv[2]) <= 0){
	  std::cerr << "error: 2nd argument must be an integral greater than zero!\n";
	  return 1;
	}

	std::cout << "Hello, ";

	for(int i = 0; i < std::atoi(argv[2]); i++){
	  std::cout << argv[1];

	  if(i + 1 != std::atoi(argv[2])){
	    std::cout << " ";
	  }
	}

	std::cout << "!\n";
  }

  //If we have no arguments
  else if(argc == 1){
  	std::cout << "Hello, world!\n";
  }
}
