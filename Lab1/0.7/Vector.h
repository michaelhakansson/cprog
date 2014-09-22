#ifndef Vector_H_OWN
#define Vector_H_OWN
#include <cstddef> // Needed for std::size_t
#include <initializer_list>
#include <type_traits>

//A container_ that can store any arbitrary number of positive integers
template <typename T> class Vector {
static_assert(std::is_move_constructible<T>::value, "This type is not move constructible");
static_assert(std::is_move_assignable<T>::value, "This type is not move assignable");
	public:
		//Default constructor
		Vector();

		//Copy constructor
		explicit Vector(const Vector&);

		//Copy assignment operator taking an Vector
		Vector& operator= (const Vector&);

		//Move constructor
		explicit Vector(Vector&&) noexcept;

		//Move assignment operator taking an Vector		
		Vector& operator=(Vector &&rsrc) noexcept;

		//s = num of zero-initialized elements to be stored
		Vector(const std::size_t&);

		Vector(const std::size_t&, const T&);

		explicit Vector(const std::initializer_list<T>);

		T& operator[](const unsigned int);

		const T& operator[](const unsigned int) const;

		//Destructor
		virtual ~Vector();

		//Assign unsigned int{} to each element in container_
		void reset();

		//Returns the number of elements in the container_
		std::size_t capacity() const;

		//Returns the number of elements in the container_
		std::size_t size() const;

		// Frees the elements in the Vector
		void free();

		//Prints each element of the container_
		void print() const;

		// Returns a pointer to the first element in the container_
		T* begin() const;

		// Returns a pointer to the element right after the last
		// element in the container_
		T* end() const;

		T* find(const T&) const;

		void push_back(const T&);

		void insert(std::size_t, T);

		void expand();

		void clear();

		void erase(std::size_t);

	private:
	T* container_;
	std::size_t capacity_;
	std::size_t size_;
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
	capacity_ = src.capacity();
	size_ = src.size();
	container_ = new T[capacity()];
	
	for(std::size_t i = 0; i < capacity(); ++i){
		container_[i] = src[i];
	}
}

// Copy assignment operator taking an Vector
template <typename T>
Vector<T>& Vector<T>::operator= (const Vector &src){
	// std::cout << "COPY ASSIGNMENT CONSTRUCTOR" << std::endl; // LOGPRINT
	if (this != &src) {
		if (capacity() != src.capacity()) {
			free();
			container_ = new T[src.capacity()];
			capacity_ = src.capacity();
			size_ = src.size();
		}
		for(std::size_t i = 0; i < capacity(); ++i) {
			container_[i] = src[i];
		}
	}
	return *this;
}


// Move constructor
template <typename T>
Vector<T>::Vector(Vector&& src) noexcept
	: container_(src.container_), capacity_(src.capacity()), size_(src.size()){
		// std::cout << "MOVE CONSTRUCTOR" << std::endl; // LOGPRINT
		src.container_ = nullptr; // Free pointer to make it safe to run destructor
		src.capacity_ = 0;
		src.size_ = 0;
	}

// Move assignment operator taking a Vector
template <typename T>
Vector<T>& Vector<T>::operator= (Vector &&src) noexcept{
	// std::cout << "MOVE ASSIGNMENT CONSTRUCTOR" << std::endl; // LOGPRINT
	if (this != &src) { // If not trying to move to itself
		free();
		container_ = src.container_;
		capacity_ = src.capacity();
		size_ = src.size();
		src.container_ = nullptr; // Free pointer to make it safe to run destructor
		src.capacity_ = 0;
		src.size_ = 0;
	}
	return *this;
}


// Constructor: size = num of uninitialized elements to be stored
template <typename T>
Vector<T>::Vector(const std::size_t& size){
	// std::cout << "SIZE_T CONSTRUCTOR" << std::endl; // LOGPRINT
	container_ = new T[size];
	capacity_ = size;
	size_ = size;
}

// Constructor: size = num of T-initialized elements with value 'value'
template <typename T>
Vector<T>::Vector(const std::size_t& size, const T& value){
	// std::cout << "SIZE_T + VALUE CONSTRUCTOR" << std::endl; // LOGPRINT
	container_ = new T[size];
	capacity_ = size;
	size_ = size;

	for(std::size_t i = 0; i < size; ++i){
		container_[i] = value;
	}
}

// Constructor: Initializer list. Add elements via Vector x = {...}
template <typename T>
Vector<T>::Vector(const std::initializer_list<T> list){
	// std::cout << "INITIALIZER LIST CONSTRUCTOR" << std::endl; // LOGPRINT
	std::size_t list_size = list.size();
	capacity_ = list_size;
	size_ = list_size;
	container_ = new T[capacity()];

	for(std::size_t i = 0; i < list_size; ++i) {
		container_[i] = list.begin()[i];
	}
}

template <typename T>
T& Vector<T>::operator[](const unsigned int x){
	if(x >= size()){
		throw std::out_of_range("Index out of bounds");
	}

	return container_[x];
}

template <typename T>
const T& Vector<T>::operator[](const unsigned int x) const{
	if(x >= size()){
		throw std::out_of_range("Index out of bounds");
	}
	return container_[x];
}


// Destructor
template <typename T>
Vector<T>::~Vector(){
	// std::cout << "DESTRUCTOR" << std::endl; // LOGPRINT
	delete[] container_;
};

// Assign unsigned int{} to each element in container_
template <typename T>
void Vector<T>::reset(){
	std::size_t size = capacity();
	for(std::size_t i = 0; i < size; i++){
		container_[i] = 0;
	}
}

// Returns the capacity for the container_
template <typename T>
std::size_t Vector<T>::capacity() const{
	return capacity_;
}

// Returns the number of elements in the container_
template <typename T>
std::size_t Vector<T>::size() const{
	return size_;
}

// Returns the number of elements in the container_
template <typename T>
void Vector<T>::free(){
	delete[] container_;
}

template <typename T>
void Vector<T>::print() const{
	std::size_t sz = size();
	if(sz > 0) {
		std::cout << "[";
		for(std::size_t i = 0; i < sz-1; ++i){
			std::cout << container_[i] << ", ";
		}
		std::cout << container_[sz-1];
		std::cout << "]" <<std::endl;
	}
}


template <typename T>
T* Vector<T>::begin() const {
	return container_;
}

template <typename T>
T* Vector<T>::end() const {
	return container_ + size();
}

template <typename T>
T* Vector<T>::find(const T& searched_element) const {
	std::size_t s = size();
	for (std::size_t i = 0; i < s ; ++i) {
		if (container_[i] == searched_element) {
			return &container_[i];
		}
	}
	return end();
}

template <typename T>
void Vector<T>::push_back(const T& elem_to_push) {
	if (capacity() <= size()) { // Must expand container_
		expand();
	}
	*end() = elem_to_push;
	++size_; //Increment size variable
}

template <typename T>
void Vector<T>::insert(const std::size_t index, const T elem) {
	if (capacity() <= size()) { // Must expand container_
		expand();
	}

	// Move all elements from index and forward one step towards the end.
	// This makes room for the new element.
	for (size_t i = size(); i > index; --i) { // Iterate backwards
		container_[i] = container_[i-1];
	}

	// Insert the new element
	container_[index] = elem;
	++size_;
}

template <typename T>
void Vector<T>::expand() {
	const std::size_t expand_factor = 2; //Factor for full container_ expansion
	std::size_t new_capacity;
	if (size() == 0) {
		new_capacity = 1;
	} else {
		new_capacity = capacity() * expand_factor;
	}
	T* new_container = new T[new_capacity];

	//Copy all elements from the old container to the new container
	for (std::size_t i = 0; i < size(); ++i) {
		new_container[i] = container_[i];
	}
	free(); //Free memory for old array
	container_ = new_container; //Repoint 'container_' pointer to new array
	capacity_ = new_capacity; //Update capacity variable
}

template <typename T>
void Vector<T>::clear() {
	free();
	container_ = new T[0];
	size_ = 0;
	capacity_ = 0;
}

template <typename T>
void Vector<T>::erase(const std::size_t index_to_remove) {
	if (index_to_remove < size()) {
		if (size() > 1) {
			// Move all elements 1 step backwards, from index_to_remove and forward
			for (std::size_t i = index_to_remove; i < size()-1; ++i) {
				container_[i] = container_[i+1];
			}
		}
		--size_;
	}
}

#endif
