// projektlokala headerfiler
#include "hypercube.hpp"

// STL headerfiler
#include <iostream>
#include <sstream>              // std::stringstream
#include <assert.h>             // assert(b) ger felmeddelande om b falsk


int main()
{
std::cout << "----------------------------------------" << std::endl;
std::cout << "Initiating tests" << std::endl;

{
    std::cout << "Testing non-default constructor" << std::endl;

    std::stringstream ss1, ss1_expected;

    // Vector with 1 element
    Hypercube<1> a(1);
    assert(a[0] == 0);
    a[0] = 1;
    assert(a[0] == 1);

    // Vector with 2 elements
    Hypercube<1> b(2); 
    assert(b[0] == 0);
    assert(b[1] == 0);
    b[0] = 1;
    b[1] = 2;
    assert(b[0] == 1);
    assert(b[1] == 2);

    // 2x2 matrix
    Hypercube<2> c(2);
    assert(c[0][0] == 0);
    assert(c[0][1] == 0);
    assert(c[1][0] == 0);
    assert(c[1][1] == 0);
    c[0][0] = 1;
    c[0][1] = 2;
    c[1][0] = 3;
    c[1][1] = 4;
    assert(c[0][0] == 1);
    assert(c[0][1] == 2);
    assert(c[1][0] == 3);
    assert(c[1][1] == 4);

    // 4x4 matrix
    Hypercube<2> d(4);
    assert(d[0][0] == 0);
    assert(d[0][1] == 0);
    assert(d[0][2] == 0);
    assert(d[0][3] == 0);
    assert(d[1][0] == 0);
    assert(d[1][1] == 0);
    assert(d[1][2] == 0);
    assert(d[1][3] == 0);
    d[0][0] = 1;
    d[0][1] = 2;
    d[0][2] = 3;
    d[0][3] = 4;
    d[1][0] = 5;
    d[1][1] = 6;
    d[1][2] = 7;
    d[1][3] = 8;
    assert(d[0][0] == 1);
    assert(d[0][1] == 2);
    assert(d[0][2] == 3);
    assert(d[0][3] == 4);
    assert(d[1][0] == 5);
    assert(d[1][1] == 6);
    assert(d[1][2] == 7);
    assert(d[1][3] == 8);

    // Cube with 2x2x2 elements
    Hypercube<3> e(2);
    assert(e[0][0][0] == 0);
    assert(e[0][0][1] == 0);
    assert(e[0][1][0] == 0);
    assert(e[0][1][1] == 0);
    assert(e[1][0][0] == 0);
    assert(e[1][0][1] == 0);
    assert(e[1][1][0] == 0);
    assert(e[1][1][1] == 0);
    e[0][0][0] = 1;
    e[0][0][1] = 2;
    e[0][1][0] = 3;
    e[0][1][1] = 4;
    e[1][0][0] = 5;
    e[1][0][1] = 6;
    e[1][1][0] = 7;
    e[1][1][1] = 8;
    assert(e[0][0][0] == 1);
    assert(e[0][0][1] == 2);
    assert(e[0][1][0] == 3);
    assert(e[0][1][1] == 4);
    assert(e[1][0][0] == 5);
    assert(e[1][0][1] == 6);
    assert(e[1][1][0] == 7);
    assert(e[1][1][1] == 8);
}

{
    std::cout << "Custom test from lab instruction" << std::endl;

    std::stringstream ss1, ss1_expected;

    Hypercube<3> n(7);    // kub med 7*7*7 element
    Hypercube<6> m(5);    // sex dimensioner, 5*5*...*5 element
    m[1][3][2][1][4][0] = 7;
    Hypercube<3> t(5);
    t = m[1][3][2];       // tilldela med del av m
    t[1][4][0] = 2;       // ändra t, ändra inte m
}


std::cout << "All tests passed!" << std::endl;
std::cout << "----------------------------------------" << std::endl;

return 0;
}

