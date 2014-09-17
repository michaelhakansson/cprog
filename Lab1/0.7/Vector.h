#ifndef Vector_HEJ
#define Vector_HEJ
#include <cstddef> // Needed for std::size_t
#include <initializer_list>
#include <type_traits>

//A container that can store any arbitrary number of positive integers
template <typename T> class Vector {
static_assert(std::is_move_constructible<T>::value, "This type is not move constructible");
static_assert(std::is_move_assignable<T>::value, "This type is not move assignable");
	public:
		//Default constructor
		Vector();

		//COPY
		//Copy constructor
		Vector(const Vector&);

		//Copy assignment operator taking an Vector
		Vector& operator= (const Vector&);


		//MOVE
		//Move constructor
		Vector(Vector&&) noexcept;


		//Move assignment operator taking an Vector		
		Vector& operator=(Vector &&rsrc) noexcept;

		//s = num of zero-initialized elements to be stored
		Vector(const std::size_t&);

		Vector(const std::size_t&, const T&);

		Vector(const std::initializer_list<T>);

		T& operator[](const unsigned int);

		const T& operator[](const unsigned int) const;

		//Destructor
		virtual ~Vector();

		//Assign unsigned int{} to each element in container
		void reset();

		//Returns the number of elements in the container
		std::size_t capacity() const;

		// Frees the elements in the Vector
		void free();

		//Prints each element of the vector
		void print() const;

	private:
	T* vector;
	std::size_t capacity_size;
};

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
	capacity_size = src.capacity();
	vector = new T[capacity()];
	
	for(size_t i = 0; i < capacity(); ++i){
		vector[i] = src[i];
	}
}

// Copy assignment operator taking an Vector
template <typename T>
Vector<T>& Vector<T>::operator= (const Vector &src){
	if (this != &src) {
		if (capacity() != src.capacity()) {
			free();
			vector = new T[src.capacity()];
			capacity_size = src.capacity();
		}
		for(size_t i = 0; i < capacity(); ++i) {
			vector[i] = src[i];
		}
	}
	return *this;
}


// Move constructor
template <typename T>
Vector<T>::Vector(Vector&& src) noexcept
	: vector(src.vector), capacity_size(src.capacity()){
		src.vector = nullptr; // Free pointer to make it safe to run destructor
		src.capacity_size = 0;
	}

// Move assignment operator taking an Vector
template <typename T>
Vector<T>& Vector<T>::operator= (Vector &&src) noexcept{
	if (this != &src) { // If not trying to move to itself
		free();
		vector = src.vector;
		capacity_size = src.capacity();
		src.vector = nullptr; // Free pointer to make it safe to run destructor
		src.capacity_size = 0;
	}
	return *this;
}


// Constructor: size = num of uninitialized elements to be stored
template <typename T>
Vector<T>::Vector(const std::size_t& size){
	vector = new T[size];
	capacity_size = size;
}

// Constructor: size = num of T-initialized elements with value 'value'
template <typename T>
Vector<T>::Vector(const std::size_t& size, const T& value){
	vector = new T[size];
	capacity_size = size;

	for(size_t i = 0; i < size; ++i){
		vector[i] = value;
	}
}

// Constructor: Initializer list. Add elements via Vector x = {...}
template <typename T>
Vector<T>::Vector(const std::initializer_list<T> list){
	size_t list_size = list.capacity();
	capacity_size = list_size;
	vector = new T[capacity()];

	for(size_t i = 0; i < list_size; ++i) {
		vector[i] = list.begin()[i];
	}
}

template <typename T>
T& Vector<T>::operator[](const unsigned int x){
	if(x >= capacity()){
		throw std::out_of_range("Index out of bounds");
	}

	return vector[x];
}

template <typename T>
const T& Vector<T>::operator[](const unsigned int x) const{
	if(x >= capacity()){
		throw std::out_of_range("Index out of bounds");
	}
	return vector[x];
}


// Destructor
template <typename T>
Vector<T>::~Vector(){
	delete[] vector;
};

// Assign unsigned int{} to each element in container
template <typename T>
void Vector<T>::reset(){
	size_t size = capacity();
	for(size_t i = 0; i < size; i++){
		vector[i] = 0;
	}
}

// Returns the number of elements in the container
template <typename T>
std::size_t Vector<T>::capacity() const{
	return capacity_size;
}

// Returns the number of elements in the container
template <typename T>
void Vector<T>::free(){
	size_t size = capacity();
	if (size != 0) {
		delete[] vector;
	}
}

template <typename T>
void Vector<T>::print() const{
	size_t size = capacity();
	if(size > 0) {
		std::cout << "[";
		for(size_t i = 0; i < size-1; ++i){
			std::cout << vector[i] << ", ";
		}
		std::cout << vector[size-1];
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


#endif
