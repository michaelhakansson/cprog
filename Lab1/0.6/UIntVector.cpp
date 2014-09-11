#include <iostream>
#include "UIntVector.h"

// Default constructor
UIntVector::UIntVector(){
	std::clog << "LOG - Default constructor" << std::endl;
}

// TODO Copy constructor
UIntVector::UIntVector(const UIntVector& src){
	UIntVector::vector_size = src.size();
	UIntVector::vector = new unsigned int[UIntVector::vector_size];
	
	// for(unsigned int i = 0; i < UIntVector::vector_size; i++){
	// 	UIntVector::vector[i] = src[i];
	// }
}


// size = num of zero-initialized elements to be stored
UIntVector::UIntVector(const std::size_t& size){
	std::clog << "LOG - CONSTRUCTOR: UIntVector::UIntVector(std::size_t const& s)" << std::endl;
	std::clog << "LOG - Initializing vector with size " << size << " and filling it with zeros." << std::endl;

	UIntVector::vector = new unsigned int[size];
	UIntVector::vector_size = size;
	
	for(unsigned int i = 0; i < size; i++){
		UIntVector::vector[i] = 0;
	}
}

// TODO
UIntVector::UIntVector(std::initializer_list<unsigned int>){}

// TODO copy-move assignment operator taking an UIntVector

unsigned int& UIntVector::operator[](const unsigned int& x){
	if(x >= UIntVector::vector_size){
		std::cerr << "Error: Index out of bounds" << std::endl;
	}

	return UIntVector::vector[x];
}

// Destructor
UIntVector::~UIntVector(){
	delete UIntVector::vector;
};

// Assign unsigned int{} to each element in container
void UIntVector::reset(){

	size_t size = UIntVector::size();

	for(unsigned int i = 0; i < size; i++){
		UIntVector::vector[i] = 0;
	}
}

// Returns the number of elements in the container
std::size_t UIntVector::size() const{
	return UIntVector::vector_size;
}

void print_vector(UIntVector* vec){
	size_t size = vec->size();
	std::cout << "ASD " << vec->size() << std::endl;

	for(size_t i = 0; i < size; i++){
		std::cout << (*vec)[i] << " ";
	}
}

int main(){
	std::clog << "LOG - FIRST IN MAIN" << std::endl;
	UIntVector a(5);
	std::cout << "IN MAIN " << a.size() << std::endl;
	a[2] = 2;
	a[4] = 4;
	print_vector(&a);
}
