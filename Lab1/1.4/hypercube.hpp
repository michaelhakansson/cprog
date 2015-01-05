// Recursive templates. See Fibonacci example here:
// http://www.cplusplus.com/forum/general/47892/

#ifndef HYPERCYBE_H_OWN
#define HYPERCYBE_H_OWN

#include "Vector.hpp"

// Recursion case
template<unsigned int dim>
class Hypercube : public Vector< Hypercube<dim-1> > {
  public:
    Hypercube(){};

    // Creates a vector with size number of hypercubes with dimension dim-1 in it.
    Hypercube (const std::size_t size) : Vector< Hypercube<dim-1> >( size, Hypercube<dim-1>(size) ) {};
};

// Base case
template<>
class Hypercube<1> : public Vector<int> {
  public:
    Hypercube(){};

    // Creates a vector with i elements where i is the number of elements
    // in each dimension - Hypercube<x>(i).
    Hypercube (const std::size_t size) : Vector<int>::Vector(size) {};
};

#endif // HYPERCYBE_H_OWN
