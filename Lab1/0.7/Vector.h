#ifndef Vector_H_OWN
#define Vector_H_OWN
#include <cstddef> // Needed for std::size_t
#include <initializer_list>
#include <type_traits>

// TODO: MAKE APPROPRIATE CONSTRUCTORS 'explicit'

//A container that can store any arbitrary number of positive integers
template <typename T> class Vector {
static_assert(std::is_move_constructible<T>::value, "This type is not move constructible");
static_assert(std::is_move_assignable<T>::value, "This type is not move assignable");
	public:
		//Default constructor
		Vector();

		//Copy constructor
		Vector(const Vector&);

		//Copy assignment operator taking an Vector
		Vector& operator= (const Vector&);

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

		//Returns the number of elements in the container
		std::size_t size() const;

		// Frees the elements in the Vector
		void free();

		//Prints each element of the vector
		void print() const;

		// Returns a pointer to the first element in the container
		T* begin() const;

		// Returns a pointer to the element right after the last
		// element in the container
		T* end() const;

		T* find(const T&) const;

		void push_back(const T&);

		void insert(std::size_t, T);

		void clear();

		void erase(std::size_t);

	private:
	T* vector;
	std::size_t my_capacity;
	std::size_t my_size;
};

#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include "Vector.h"

// Default constructor
template <typename T>
Vector<T>::Vector() : Vector<T>::Vector(0) {
	// std::cout << "DEFAULT CONSTRUCTOR" << std::endl; // LOGPRINT
	//Delegating constructor to Vector(0)
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector& src){
	// std::cout << "COPY CONSTRUCTOR" << std::endl; // LOGPRINT
	my_capacity = src.capacity();
	my_size = src.size();
	vector = new T[capacity()];
	
	for(size_t i = 0; i < capacity(); ++i){
		vector[i] = src[i];
	}
}

// Copy assignment operator taking an Vector
template <typename T>
Vector<T>& Vector<T>::operator= (const Vector &src){
	// std::cout << "COPY ASSIGNMENT CONSTRUCTOR" << std::endl; // LOGPRINT
	if (this != &src) {
		if (capacity() != src.capacity()) {
			free();
			vector = new T[src.capacity()];
			my_capacity = src.capacity();
			my_size = src.size();
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
	: vector(src.vector), my_capacity(src.capacity()), my_size(src.size()){
		// std::cout << "MOVE CONSTRUCTOR" << std::endl; // LOGPRINT
		src.vector = nullptr; // Free pointer to make it safe to run destructor
		src.my_capacity = 0;
		src.my_size = 0;
	}

// Move assignment operator taking a Vector
template <typename T>
Vector<T>& Vector<T>::operator= (Vector &&src) noexcept{
	// std::cout << "MOVE ASSIGNMENT CONSTRUCTOR" << std::endl; // LOGPRINT
	if (this != &src) { // If not trying to move to itself
		free();
		vector = src.vector;
		my_capacity = src.capacity();
		my_size = src.size();
		src.vector = nullptr; // Free pointer to make it safe to run destructor
		src.my_capacity = 0;
		src.my_size = 0;
	}
	return *this;
}


// Constructor: size = num of uninitialized elements to be stored
template <typename T>
Vector<T>::Vector(const std::size_t& size){
	// std::cout << "SIZE_T CONSTRUCTOR" << std::endl; // LOGPRINT
	vector = new T[size];
	my_capacity = size;
	my_size = size;
}

// Constructor: size = num of T-initialized elements with value 'value'
template <typename T>
Vector<T>::Vector(const std::size_t& size, const T& value){
	// std::cout << "SIZE_T + VALUE CONSTRUCTOR" << std::endl; // LOGPRINT
	vector = new T[size];
	my_capacity = size;
	my_size = size;

	for(size_t i = 0; i < size; ++i){
		vector[i] = value;
	}
}

// Constructor: Initializer list. Add elements via Vector x = {...}
template <typename T>
Vector<T>::Vector(const std::initializer_list<T> list){
	// std::cout << "INITIALIZER LIST CONSTRUCTOR" << std::endl; // LOGPRINT
	size_t list_size = list.size();
	my_capacity = list_size;
	my_size = list_size;
	vector = new T[capacity()];

	for(size_t i = 0; i < list_size; ++i) {
		vector[i] = list.begin()[i];
	}
}

template <typename T>
T& Vector<T>::operator[](const unsigned int x){
	if(x >= size()){
		throw std::out_of_range("Index out of bounds");
	}

	return vector[x];
}

template <typename T>
const T& Vector<T>::operator[](const unsigned int x) const{
	if(x >= size()){
		throw std::out_of_range("Index out of bounds");
	}
	return vector[x];
}


// Destructor
template <typename T>
Vector<T>::~Vector(){
	// std::cout << "DESTRUCTOR" << std::endl; // LOGPRINT
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

// Returns the capacity for the container
template <typename T>
std::size_t Vector<T>::capacity() const{
	return my_capacity;
}

// Returns the number of elements in the container
template <typename T>
std::size_t Vector<T>::size() const{
	return my_size;
}

// Returns the number of elements in the container
template <typename T>
void Vector<T>::free(){
	// std::cout << "FREE FUNCTION" << std::endl; // LOGPRINT
	// size_t size = capacity();
	// if (size != 0) { // TODO: This was our memory leak. Should probably
						// be fixed in UIntVector as well.
		delete[] vector;
	// }
}

template <typename T>
void Vector<T>::print() const{
	size_t sz = size();
	if(sz > 0) {
		std::cout << "[";
		for(size_t i = 0; i < sz-1; ++i){
			std::cout << vector[i] << ", ";
		}
		std::cout << vector[sz-1];
		std::cout << "]" <<std::endl;
	}
}


template <typename T>
T* Vector<T>::begin() const {
	return vector;
}

template <typename T>
T* Vector<T>::end() const {
	return vector + size();
}

template <typename T>
T* Vector<T>::find(const T& searched_element) const {
	size_t s = size();
	for (size_t i = 0; i < s ; ++i) {
		if (vector[i] == searched_element) {
			return &vector[i];
		}
	}
	return end();
}


//TODO: Refactor to have a expand container function
template <typename T>
void Vector<T>::push_back(const T& elem_to_push) {
	if (capacity() <= size()) { //Must expand container
		size_t expand_factor = 2; //Factor for full container expansion
		// Create new vector with 'expand_factor' as much capacity
		size_t new_capacity = expand_factor * (capacity()+1); //+1 to cover 0-size container case
		T* new_vector = new T[new_capacity];
		for (size_t i = 0; i < size(); ++i) { //Copy all old elements to new
			new_vector[i] = vector[i];
		}
		free(); //Free memory for old array
		vector = new_vector; //Repoint 'vector' pointer to new array
		my_capacity = new_capacity; //Update capacity variable
	}	
	*end() = elem_to_push;
	++my_size; //Increment size variable
}

template <typename T>
void Vector<T>::insert(std::size_t index, T elem) {
	//TODO
}

template <typename T>
void Vector<T>::clear() {
	free();
	vector = new T[0];
	my_size = 0;
	my_capacity = 0;
}

template <typename T>
void Vector<T>::erase(std::size_t index_to_remove) {
	//TODO
}

#endif
