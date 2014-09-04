#include <iostream>

void translation(char * name, int number){

  //If we have no arguments
  if(name == NULL){
  	std::cout << "Hello, world!\n";
  }

  //If we have a name
  else if(number == 1){
    std::cout << "Hello, " << name << "!\n"; 
  }

  else if(number <= 0){
	std::cerr << "error: 2nd argument must be an integral greater than zero!\n";
	return;
  }

  else{
	std::cout << "Hello, ";

	for(int i = 0; i < number; i++){
	  std::cout << name;

	  if(i + 1 != number){
	    std::cout << " ";
	  }
	}

	std::cout << "!\n";
  }

  return;
}
