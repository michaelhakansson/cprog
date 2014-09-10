#include <iostream>
#include "UIntVector.h"

// Default constructor
UIntVector::UIntVector(): vector(new unsigned int[20]){
	std::clog << "LOG - Default constructor" << std::endl;
}


//Copy constructor
UIntVector::UIntVector(const UIntVector& src){}

//TODO Move constructor

//s = num of zero-initialized elements to be stored
UIntVector::UIntVector(const std::size_t& size){
	std::clog << "LOG - CONSTRUCTOR: UIntVector::UIntVector(std::size_t const& s)" << std::endl;
	std::clog << "LOG - Initializing vector with size " << size << " and filling it with zeros." << std::endl;
}

UIntVector::UIntVector(std::initializer_list<unsigned int>){}

//TODO copy-move assignment operator taking an UIntVector

//TODO overload operator [] to be able to access modify element at index

//Destructor
//UIntVector::~UIntVector();

//Assign unsigned int{} to each element in container
void UIntVector::reset(){}

//Returns the number of elements in the container
std::size_t UIntVector::size(){
	return 0; // TODO
}

int main(){
	std::clog << "LOG - FIRST IN MAIN" << std::endl;
	UIntVector a(1);
}
