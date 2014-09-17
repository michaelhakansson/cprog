#ifndef Vector_HEJ
#define Vector_HEJ
#include <cstddef> // Needed for std::size_t
#include <initializer_list>

//A container that can store any arbitrary number of positive integers
template <typename T> class Vector {
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
		std::size_t size() const;

		// Frees the elements in the Vector
		void free();

		//Prints each element of the vector
		void print() const;

	private:
	T* vector;
	std::size_t vector_size;

};

#endif
