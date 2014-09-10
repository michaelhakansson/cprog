//#ifndef UINTVECTOR_H
//#define UINTVECTOR_H
#include <cstddef> // Needed for std::size_t
#include <initializer_list>

//A container that can store any arbitrary number of positive integers
class UIntVector{

	private:
	unsigned int[] vector;

	public:
		//Default constructor
		UIntVector();

		
		//Copy constructor
		UIntVector(const UIntVector& src);

		//TODO Move constructor

		//s = num of zero-initialized elements to be stored
		UIntVector(const std::size_t& size);

		UIntVector(std::initializer_list<unsigned int> list);

		//TODO copy-move assignment operator taking an UIntVector

		//TODO overload operator [] to be able to access modify element at index

		//Destructor
		~UIntVector(){};

		//Assign unsigned int{} to each element in container
		void reset();

		//Returns the number of elements in the container
		std::size_t size();
};

//#endif
