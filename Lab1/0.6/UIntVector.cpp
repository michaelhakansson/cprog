#include <iostream>
#include "UIntVector.h"

// Default constructor
UIntVector::UIntVector(){
	std::clog << "LOG - Default constructor" << std::endl;
}

// Copy constructor
UIntVector::UIntVector(const UIntVector& src){
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

UIntVector::UIntVector(std::initializer_list<unsigned int>){}

// TODO copy-move assignment operator taking an UIntVector

// TODO overload operator [] to be able to access modify element at index
unsigned int& UIntVector::operator[](const unsigned int& x){

	if(x >= UIntVector::vector_size){
		std::cerr << "Index out of bounds\n";
	}

	return UIntVector::vector[x];
}

// Destructor
UIntVector::~UIntVector(){
	delete UIntVector::vector;
};

// Assign unsigned int{} to each element in container
void UIntVector::reset(){

	unsigned int size = UIntVector::size();

	for(unsigned int i = 0; i < size; i++){
		UIntVector::vector[i] = 0;
	}
}

// Returns the number of elements in the container
std::size_t UIntVector::size() const{
	return UIntVector::vector_size;
}

void print_vector(UIntVector vec){
	unsigned int size = vec.size();

	for(unsigned int i = 0; i < size; i++){
		std::cout << vec[i] << " ";
	}
}

int main(){
	std::clog << "LOG - FIRST IN MAIN" << std::endl;
	UIntVector a(5);
	a[2] = 2;
	a[4] = 4;
	print_vector(a);
}

