#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include "Vector.h"

// Default constructor
template <typename T>
Vector<T>::Vector() : Vector<T>::Vector(0) {
	//Delegating constructor to Vector(0)
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector& src){
	Vector<T>::vector_size = src.size();
	Vector<T>::vector = new unsigned int[Vector<T>::vector_size];
	
	for(unsigned int i = 0; i < Vector<T>::vector_size; ++i){
		Vector<T>::vector[i] = src[i];
	}
}

// Copy assignment operator taking an Vector
template <typename T>
Vector<T>& Vector<T>::operator= (const Vector &src){
	if (this != &src) {
		if (Vector<T>::vector_size != src.vector_size) {
			Vector<T>::free();
			Vector<T>::vector = new unsigned int[src.vector_size];
			Vector<T>::vector_size = src.vector_size;
		}
		for(unsigned int i = 0; i < Vector<T>::vector_size; ++i) {
			Vector<T>::vector[i] = src[i];
		}
	}
	return *this;
}


// Move constructor
template <typename T>
Vector<T>::Vector(Vector&& src) noexcept
	: vector(src.vector), vector_size(src.vector_size){
		src.vector = nullptr; // Free pointer to make it safe to run destructor
		src.vector_size = 0;
	}

// Move assignment operator taking an Vector
template <typename T>
Vector<T>& Vector<T>::operator= (Vector &&src) noexcept{
	if (this != &src) { // If not trying to move to itself
		Vector<T>::free();
		Vector<T>::vector = src.vector;
		Vector<T>::vector_size = src.vector_size;
		src.vector = nullptr; // Free pointer to make it safe to run destructor
		src.vector_size = 0;
	}
	return *this;
}


// Constructor: size = num of zero-initialized elements to be stored
template <typename T>
Vector<T>::Vector(const std::size_t& size){
	Vector<T>::vector = new T[size];
	Vector<T>::vector_size = size;
	
	for(size_t i = 0; i < size; ++i){
		Vector<T>::vector[i] = 0;
	}
}

// Constructor: Initializer list. Add elements via Vector x = {...}
template <typename T>
Vector<T>::Vector(const std::initializer_list<T> list){
	unsigned int list_size = list.size();
	Vector<T>::vector_size = list_size;
	Vector<T>::vector = new T[Vector<T>::vector_size];

	for(unsigned int i = 0; i < list_size; ++i) {
		Vector<T>::vector[i] = list.begin()[i];
	}
}

template <typename T>
T& Vector<T>::operator[](const unsigned int x){
	if(x >= Vector<T>::vector_size){
		throw std::out_of_range("Index out of bounds");
	}

	return Vector<T>::vector[x];
}

template <typename T>
const T& Vector<T>::operator[](const unsigned int x) const{
	if(x >= Vector<T>::vector_size){
		throw std::out_of_range("Index out of bounds");
	}
	return Vector<T>::vector[x];
}


// Destructor
template <typename T>
Vector<T>::~Vector(){
	delete[] Vector<T>::vector;
};

// Assign unsigned int{} to each element in container
template <typename T>
void Vector<T>::reset(){
	size_t size = Vector<T>::size();
	for(unsigned int i = 0; i < size; i++){
		Vector<T>::vector[i] = 0;
	}
}

// Returns the number of elements in the container
template <typename T>
std::size_t Vector<T>::size() const{
	return Vector<T>::vector_size;
}

// Returns the number of elements in the container
template <typename T>
void Vector<T>::free(){
	size_t size = Vector<T>::size();
	if (size != 0) {
		delete[] Vector<T>::vector;
	}
}

template <typename T>
void Vector<T>::print() const{
	size_t size = Vector<T>::vector_size;
	if(size > 0) {
		std::cout << "[";
		for(size_t i = 0; i < size-1; ++i){
			std::cout << Vector<T>::vector[i] << ", ";
		}
		std::cout << Vector<T>::vector[size-1];
		std::cout << "]" <<std::endl;
	}
}

// int main(){
// 	Vector a(5); // Initialize 5 zero-elements
// 	a[2] = 2;
// 	a[4] = 4;
// 	Vector b = {1,2,3}; // Initialize with initialization list
// 	a.print();
// 	b.print();
// 	Vector c = b; // Use copy constructor
// 	c.print();
// 	Vector d(std::move(a));
// 	d.print();
// 	a = std::move(b);
// 	a.print();
// 	c = d;
// 	c.print();
// }
