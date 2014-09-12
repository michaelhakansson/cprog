#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include "UIntVector.h"

// Default constructor
UIntVector::UIntVector(){
	std::clog << "LOG - Default constructor" << std::endl;
}

// Copy constructor
UIntVector::UIntVector(const UIntVector& src){
	UIntVector::vector_size = src.size();
	UIntVector::vector = new unsigned int[UIntVector::vector_size];
	
	for(unsigned int i = 0; i < UIntVector::vector_size; ++i){
		UIntVector::vector[i] = src[i];
	}
}


// TODO: copy assignment operator taking an UIntVector


//TODO: Move constructor
UIntVector::UIntVector(UIntVector&& src) noexcept
	: vector_size(src.vector_size), vector(src.vector) {
		std::cout << "MOVE CONSTRUCTOR" << std::endl;
		src.vector = nullptr; // Free pointer to make it safe to run destructor
		// TODO: Need to free src.vector_size somehow?
	}

// TODO: move assignment operator taking an UIntVector
UIntVector& UIntVector::operator=(UIntVector &&rhs) noexcept {
	if (this != &rhs) { // If not trying to move to itself
		// TODO: Free (deallocate) lhs elements
		UIntVector::vector = rhs.vector;
		UIntVector::vector_size = rhs.vector_size;
		rhs.vector = nullptr; // Free pointer to make it safe to run destructor
		// TODO: Need to free rhs.vector_size somehow?
	}
	return *this;
}


// Constructor: size = num of zero-initialized elements to be stored
UIntVector::UIntVector(const std::size_t& size){
	UIntVector::vector = new unsigned int[size];
	UIntVector::vector_size = size;
	
	for(unsigned int i = 0; i < size; ++i){
		UIntVector::vector[i] = 0;
	}
}

// Constructor: Initializer list. Add elements via UIntVector x = {...}
UIntVector::UIntVector(const std::initializer_list<unsigned int> list){
	unsigned int list_size = list.size();
	UIntVector::vector_size = list_size;
	UIntVector::vector = new unsigned int[UIntVector::vector_size];

	for(int i = 0; i < list_size; ++i) {
		UIntVector::vector[i] = list.begin()[i];
	}
}

unsigned int& UIntVector::operator[](const unsigned int x){
	if(x >= UIntVector::vector_size){
		throw std::out_of_range("Index out of bounds");
	}

	return UIntVector::vector[x];
}

const unsigned int& UIntVector::operator[](const unsigned int x) const{
	if(x >= UIntVector::vector_size){
		throw std::out_of_range("Index out of bounds");
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

void UIntVector::print() const{
	size_t size = UIntVector::vector_size;
	std::cout << "[";
	for(size_t i = 0; i < size-1; i++){
		std::cout << UIntVector::vector[i] << ", ";
	}
	std::cout << UIntVector::vector[size-1];
	std::cout << "]" <<std::endl;
}

int main(){
	UIntVector a(5); // Initialize 5 zero-elements
	a[2] = 2;
	a[4] = 4;
	UIntVector b = {1,2,3}; // Initialize with initialization list
	a.print();
	b.print();
	UIntVector c = b; // Use copy constructor
	c.print();
	UIntVector d(std::move(a));
	d.print();
}
