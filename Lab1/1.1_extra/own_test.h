#ifndef MATRIX_TEST_H_INCLUDED
#define MATRIX_TEST_H_INCLUDED

#include "Matrix_not_our.h"
#include "/info/cprog09/cxxtest/cxxtest/TestSuite.h"
#include <fstream>
#include <sstream>

class MatrixTestSuite : public CxxTest::TestSuite
{

    Matrix a_matrix_3by2() {    // [ 1 3 5 ]
        Matrix m;               // [ 0 2 0 ]
        std::stringstream s("  [ 1 3 5 ; 0 2 0 ]");
        s >> m;
        return m;
    }

    void init_matrix( Matrix& m, const char* file )
    {
        std::stringstream stream( file );   
        stream >> m;
    }

public:
    void testIndexOperator ( )
    {
        Matrix m( 2, 2 );
        TS_ASSERT( m[ 0 ][ 1 ] == 0 );

        m = a_matrix_3by2();
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );

        init_matrix(m, "  [ 1 3 5 ; 0 2 1 ]");
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );

        std::stringstream ss;
        ss << m;
        ss >> m;
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );
    }


    // HERE COMES OUR TESTS

    void testrow_col_init_init_values () {
        Matrix a(2,3);
        TS_ASSERT_EQUALS(a[0][0], 0);
        TS_ASSERT_EQUALS(a[0][1], 0);
        TS_ASSERT_EQUALS(a[0][2], 0);
        TS_ASSERT_EQUALS(a[1][0], 0);
        TS_ASSERT_EQUALS(a[1][1], 0);
        TS_ASSERT_EQUALS(a[1][2], 0);
    }

    void testrow_col_init_out_of_range_check () {
        Matrix a(2,3);
        TS_ASSERT_THROWS_NOTHING(a[0][0]);
        TS_ASSERT_THROWS_NOTHING(a[0][1]);
        TS_ASSERT_THROWS_NOTHING(a[0][2]);
        TS_ASSERT_THROWS_NOTHING(a[1][0]);
        TS_ASSERT_THROWS_NOTHING(a[1][1]);
        TS_ASSERT_THROWS_NOTHING(a[1][2]);
        TS_ASSERT_THROWS(a[2][0], std::out_of_range);
        TS_ASSERT_THROWS(a[0][3], std::out_of_range);
    }


    void testassignment_correct_values () {
        Matrix a(2,2);
        a[0][0] = 1;
        a[0][1] = 2;
        a[1][0] = 3;
        a[1][1] = 4;
        TS_ASSERT_EQUALS(a[0][0], 1);
        TS_ASSERT_EQUALS(a[0][1], 2);
        TS_ASSERT_EQUALS(a[1][0], 3);
        TS_ASSERT_EQUALS(a[1][1], 4);
    }

    void testidentity_initiation () {
        Matrix a(1);
        TS_ASSERT_EQUALS(a[0][0], 1);
        
        Matrix b(2);
        TS_ASSERT_EQUALS(b[0][0], 1);
        TS_ASSERT_EQUALS(b[0][1], 0);
        TS_ASSERT_EQUALS(b[1][0], 0);
        TS_ASSERT_EQUALS(b[1][1], 1);

        Matrix c(5);
        TS_ASSERT_EQUALS(c[0][0], 1);
        TS_ASSERT_EQUALS(c[0][1], 0);
        TS_ASSERT_EQUALS(c[0][2], 0);
        TS_ASSERT_EQUALS(c[0][3], 0);
        TS_ASSERT_EQUALS(c[0][4], 0);
        TS_ASSERT_EQUALS(c[1][0], 0);
        TS_ASSERT_EQUALS(c[1][1], 1);
        TS_ASSERT_EQUALS(c[1][2], 0);
        TS_ASSERT_EQUALS(c[1][3], 0);
        TS_ASSERT_EQUALS(c[1][4], 0);
        TS_ASSERT_EQUALS(c[2][0], 0);
        TS_ASSERT_EQUALS(c[2][1], 0);
        TS_ASSERT_EQUALS(c[2][2], 1);
        TS_ASSERT_EQUALS(c[2][3], 0);
        TS_ASSERT_EQUALS(c[2][4], 0);
        TS_ASSERT_EQUALS(c[3][0], 0);
        TS_ASSERT_EQUALS(c[3][1], 0);
        TS_ASSERT_EQUALS(c[3][2], 0);
        TS_ASSERT_EQUALS(c[3][3], 1);
        TS_ASSERT_EQUALS(c[3][4], 0);
        TS_ASSERT_EQUALS(c[4][0], 0);
        TS_ASSERT_EQUALS(c[4][1], 0);
        TS_ASSERT_EQUALS(c[4][2], 0);
        TS_ASSERT_EQUALS(c[4][3], 0);
        TS_ASSERT_EQUALS(c[4][4], 1);
    }


    void testindex_operator_index_out_of_bounds_check () {
        Matrix a(3);
        TS_ASSERT_THROWS_NOTHING(a[0][0]);
        TS_ASSERT_THROWS_NOTHING(a[0][1]);
        TS_ASSERT_THROWS_NOTHING(a[0][2]);
        TS_ASSERT_THROWS_NOTHING(a[1][0]);
        TS_ASSERT_THROWS_NOTHING(a[1][1]);
        TS_ASSERT_THROWS_NOTHING(a[1][2]);
        TS_ASSERT_THROWS_NOTHING(a[2][0]);
        TS_ASSERT_THROWS_NOTHING(a[2][1]);
        TS_ASSERT_THROWS_NOTHING(a[2][2]);
        TS_ASSERT_THROWS(a[3][0], std::out_of_range);
        TS_ASSERT_THROWS(a[0][3], std::out_of_range);
    }

    void testinput_to_empty_matrix () {
        Matrix a;
        std::stringstream ss("  [ 1 3 5 ; 0 2 0 ]");
        ss >> a;
        TS_ASSERT_EQUALS(a[0][0], 1);
        TS_ASSERT_EQUALS(a[0][1], 3);
        TS_ASSERT_EQUALS(a[0][2], 5);
        TS_ASSERT_EQUALS(a[1][0], 0);
        TS_ASSERT_EQUALS(a[1][1], 2);
        TS_ASSERT_EQUALS(a[1][2], 0);
    }

    void testinput_to_larger_matrix () {
        Matrix a(4,4);
        std::stringstream ss("  [ 1 3 5 ; 0 2 0 ]");
        ss >> a;
        TS_ASSERT_EQUALS(a[0][0], 1);
        TS_ASSERT_EQUALS(a[0][1], 3);
        TS_ASSERT_EQUALS(a[0][2], 5);
        TS_ASSERT_EQUALS(a[1][0], 0);
        TS_ASSERT_EQUALS(a[1][1], 2);
        TS_ASSERT_EQUALS(a[1][2], 0);
        TS_ASSERT_THROWS(a[3][0], std::out_of_range);
        TS_ASSERT_THROWS(a[0][3], std::out_of_range);
    }

    void testinput_to_smaller_matrix () {
        Matrix a(2,2);
        std::stringstream ss("  [ 1 3 5 ; 0 2 0 ]");
        ss >> a;
        TS_ASSERT_EQUALS(a[0][0], 1);
        TS_ASSERT_EQUALS(a[0][1], 3);
        TS_ASSERT_EQUALS(a[0][2], 5);
        TS_ASSERT_EQUALS(a[1][0], 0);
        TS_ASSERT_EQUALS(a[1][1], 2);
        TS_ASSERT_EQUALS(a[1][2], 0);
        TS_ASSERT_THROWS(a[3][0], std::out_of_range);
        TS_ASSERT_THROWS(a[0][3], std::out_of_range);
    }

    void testoutputtest () {
        Matrix a(3);
        Matrix b;
        std::stringstream ss;
        ss << a;
        ss >> b;
        TS_ASSERT_EQUALS(b[0][0], a[0][0]);
        TS_ASSERT_EQUALS(b[0][1], a[0][1]);
        TS_ASSERT_EQUALS(b[0][2], a[0][2]);
        TS_ASSERT_EQUALS(b[1][0], a[1][0]);
        TS_ASSERT_EQUALS(b[1][1], a[1][1]);
        TS_ASSERT_EQUALS(b[1][2], a[1][2]);
        TS_ASSERT_EQUALS(b[2][0], a[2][0]);
        TS_ASSERT_EQUALS(b[2][1], a[2][1]);
        TS_ASSERT_EQUALS(b[2][2], a[2][2]);
    }

    void testscalar_mult_positive_scalar () {
        Matrix a(3,2);
        a[0][0] = 0;
        a[0][1] = 1;
        a[1][0] = 2;
        a[1][1] = 3;
        a[2][0] = 4;
        a[2][1] = 5;

        int scalar = 3;
        Matrix b;
        b = a * scalar;

        TS_ASSERT_EQUALS(b[0][0], 0);
        TS_ASSERT_EQUALS(b[0][1], 3);
        TS_ASSERT_EQUALS(b[1][0], 6);
        TS_ASSERT_EQUALS(b[1][1], 9);
        TS_ASSERT_EQUALS(b[2][0], 12);
        TS_ASSERT_EQUALS(b[2][1], 15);

        TS_ASSERT_EQUALS(a[0][0], 0);
        TS_ASSERT_EQUALS(a[0][1], 1);
        TS_ASSERT_EQUALS(a[1][0], 2);
        TS_ASSERT_EQUALS(a[1][1], 3);
        TS_ASSERT_EQUALS(a[2][0], 4);
        TS_ASSERT_EQUALS(a[2][1], 5);


        Matrix c;
        c = scalar * a;
        TS_ASSERT_EQUALS(c[0][0], 0);
        TS_ASSERT_EQUALS(c[0][1], 3);
        TS_ASSERT_EQUALS(c[1][0], 6);
        TS_ASSERT_EQUALS(c[1][1], 9);
        TS_ASSERT_EQUALS(c[2][0], 12);
        TS_ASSERT_EQUALS(c[2][1], 15);

        TS_ASSERT_EQUALS(a[0][0], 0);
        TS_ASSERT_EQUALS(a[0][1], 1);
        TS_ASSERT_EQUALS(a[1][0], 2);
        TS_ASSERT_EQUALS(a[1][1], 3);
        TS_ASSERT_EQUALS(a[2][0], 4);
        TS_ASSERT_EQUALS(a[2][1], 5);
    }

    void testscalar_mult_negative_scalar () {
        Matrix a(2,3);
        a[0][0] = 0;
        a[0][1] = 1;
        a[0][2] = 2;
        a[1][0] = 3;
        a[1][1] = 4;
        a[1][2] = 5;

        int scalar = -3;
        Matrix b;
        b = scalar * a;
        TS_ASSERT_EQUALS(b[0][0], 0);
        TS_ASSERT_EQUALS(b[0][1], -3);
        TS_ASSERT_EQUALS(b[0][2], -6);
        TS_ASSERT_EQUALS(b[1][0], -9);
        TS_ASSERT_EQUALS(b[1][1], -12);
        TS_ASSERT_EQUALS(b[1][2], -15);

        Matrix c;
        c = a * scalar;
        TS_ASSERT_EQUALS(c[0][0], 0);
        TS_ASSERT_EQUALS(c[0][1], -3);
        TS_ASSERT_EQUALS(c[0][2], -6);
        TS_ASSERT_EQUALS(c[1][0], -9);
        TS_ASSERT_EQUALS(c[1][1], -12);
        TS_ASSERT_EQUALS(c[1][2], -15);

        TS_ASSERT_EQUALS(a[0][0], 0);
        TS_ASSERT_EQUALS(a[0][1], 1);
        TS_ASSERT_EQUALS(a[0][2], 2);
        TS_ASSERT_EQUALS(a[1][0], 3);
        TS_ASSERT_EQUALS(a[1][1], 4);
        TS_ASSERT_EQUALS(a[1][2], 5);
    }

    void testscalar_mult_zero_scalar () {
        Matrix a(2,3);
        a[0][0] = 0;
        a[0][1] = 1;
        a[0][2] = 2;
        a[1][0] = 3;
        a[1][1] = 4;
        a[1][2] = 5;

        int scalar = 0;
        Matrix b;
        b = scalar * a;
        TS_ASSERT_EQUALS(b[0][0], 0);
        TS_ASSERT_EQUALS(b[0][1], 0);
        TS_ASSERT_EQUALS(b[0][2], 0);
        TS_ASSERT_EQUALS(b[1][0], 0);
        TS_ASSERT_EQUALS(b[1][1], 0);
        TS_ASSERT_EQUALS(b[1][2], 0);

        Matrix c;
        c = a * scalar;
        TS_ASSERT_EQUALS(c[0][0], 0);
        TS_ASSERT_EQUALS(c[0][1], 0);
        TS_ASSERT_EQUALS(c[0][2], 0);
        TS_ASSERT_EQUALS(c[1][0], 0);
        TS_ASSERT_EQUALS(c[1][1], 0);
        TS_ASSERT_EQUALS(c[1][2], 0);

        TS_ASSERT_EQUALS(a[0][0], 0);
        TS_ASSERT_EQUALS(a[0][1], 1);
        TS_ASSERT_EQUALS(a[0][2], 2);
        TS_ASSERT_EQUALS(a[1][0], 3);
        TS_ASSERT_EQUALS(a[1][1], 4);
        TS_ASSERT_EQUALS(a[1][2], 5);
    }

    void testscalar_mult_multiply_self () {
        Matrix a(2,3);
        a[0][0] = 0;
        a[0][1] = 1;
        a[0][2] = 2;
        a[1][0] = 3;
        a[1][1] = 4;
        a[1][2] = 5;

        int scalar = 3;
        a = a * scalar;
        TS_ASSERT_EQUALS(a[0][0], 0);
        TS_ASSERT_EQUALS(a[0][1], 3);
        TS_ASSERT_EQUALS(a[0][2], 6);
        TS_ASSERT_EQUALS(a[1][0], 9);
        TS_ASSERT_EQUALS(a[1][1], 12);
        TS_ASSERT_EQUALS(a[1][2], 15);
    }

    // TODO: CHECK IF THIS IS THE EXPECTED BEHAVIOUR
    void testscalar_mult_size_zero () {
        Matrix a(0);
        int scalar = 3;
        a = a * scalar;
        TS_ASSERT_THROWS(a[0][0], std::out_of_range);
    }

    void testscalar_mult_size_one () {
        Matrix a(1);

        int scalar = 3;
        a = a * scalar;
        TS_ASSERT_EQUALS(a[0][0], 3);
    }

    void testmatrix_mult_test () {
        Matrix a(2,3);
        a[0][0] = 0;
        a[0][1] = 1;
        a[0][2] = 2;
        a[1][0] = 3;
        a[1][1] = 4;
        a[1][2] = 5;

        Matrix b(3,2);
        b[0][0] = 0;
        b[0][1] = 1;
        b[1][0] = 2;
        b[1][1] = 3;
        b[2][0] = 4;
        b[2][1] = 5;

        Matrix test1;
        test1 = a * b;
        TS_ASSERT_EQUALS(test1[0][0], 10);
        TS_ASSERT_EQUALS(test1[0][1], 13);
        TS_ASSERT_EQUALS(test1[1][0], 28);
        TS_ASSERT_EQUALS(test1[1][1], 40);
        TS_ASSERT_THROWS(test1[0][2], std::out_of_range);
        TS_ASSERT_THROWS(test1[2][0], std::out_of_range);


        Matrix test2;
        test2 = b * a;
        TS_ASSERT_EQUALS(test2[0][0], 3);
        TS_ASSERT_EQUALS(test2[0][1], 4);
        TS_ASSERT_EQUALS(test2[0][2], 5);
        TS_ASSERT_EQUALS(test2[1][0], 9);
        TS_ASSERT_EQUALS(test2[1][1], 14);
        TS_ASSERT_EQUALS(test2[1][2], 19);
        TS_ASSERT_EQUALS(test2[2][0], 15);
        TS_ASSERT_EQUALS(test2[2][1], 24);
        TS_ASSERT_EQUALS(test2[2][2], 33);
        TS_ASSERT_THROWS(test2[0][3], std::out_of_range);
        TS_ASSERT_THROWS(test2[3][0], std::out_of_range);
    }

    void testmatrix_mult_non_compatible_sizes () {
        Matrix a(3,3);
        Matrix b(3,2);
        Matrix c(2,3);

        TS_ASSERT_THROWS_NOTHING(a*b);
        TS_ASSERT_THROWS_ANYTHING(b*a);

        TS_ASSERT_THROWS_ANYTHING(a*c);
        TS_ASSERT_THROWS_NOTHING(c*a);
    }

    // TODO: CHECK IF THIS IS THE EXPECTED BEHAVIOUR
    void testmatrix_mult_size_zero () {
        Matrix a(0);
        Matrix b(0);
        a = a * b;
        TS_ASSERT_THROWS(a[0][0], std::out_of_range);
    }

    void testmatrix_mult_size_one () {
        Matrix a(1,1);
        Matrix b(1,1);
        a[0][0] = 2;
        b[0][0] = 4;

        a = a * b;
        TS_ASSERT_EQUALS(a[0][0], 8);
        TS_ASSERT_EQUALS(b[0][0], 4);

    }

    void testmatrix_addition_test () {
        Matrix a;
        Matrix b;

        std::stringstream("[1 2 0 ; 9 8 7]") >> a;
        std::stringstream("[3 4 1 ; 9 1 7]") >> b;

        Matrix c;
        c = a + b;

        TS_ASSERT_EQUALS(c[0][0], 4);
        TS_ASSERT_EQUALS(c[0][1], 6);
        TS_ASSERT_EQUALS(c[0][2], 1);
        TS_ASSERT_EQUALS(c[1][0], 18);
        TS_ASSERT_EQUALS(c[1][1], 9);
        TS_ASSERT_EQUALS(c[1][2], 14);
    }

    void testmatrix_addition_non_compatible_sizes () {
        Matrix a(3,3);
        Matrix b(3,2);
        Matrix c(2,3);

        TS_ASSERT_THROWS_ANYTHING(a+b);
        TS_ASSERT_THROWS_ANYTHING(b+a);

        TS_ASSERT_THROWS_ANYTHING(a+c);
        TS_ASSERT_THROWS_ANYTHING(c+a);

        TS_ASSERT_THROWS_ANYTHING(b+c);
        TS_ASSERT_THROWS_ANYTHING(c+b);
    }

    void testmatrix_subtraction_test () {
        Matrix a;
        Matrix b;

        std::stringstream("[1 2 0 ; 9 8 7]") >> a;
        std::stringstream("[3 4 1 ; 9 1 7]") >> b;

        Matrix c;
        c = a - b;

        TS_ASSERT_EQUALS(c[0][0], -2);
        TS_ASSERT_EQUALS(c[0][1], -2);
        TS_ASSERT_EQUALS(c[0][2], -1);
        TS_ASSERT_EQUALS(c[1][0], 0);
        TS_ASSERT_EQUALS(c[1][1], 7);
        TS_ASSERT_EQUALS(c[1][2], 0);
    }

    void testmatrix_subtraction_non_compatible_sizes () {
        Matrix a(3,3);
        Matrix b(3,2);
        Matrix c(2,3);

        TS_ASSERT_THROWS_ANYTHING(a-b);
        TS_ASSERT_THROWS_ANYTHING(b-a);

        TS_ASSERT_THROWS_ANYTHING(a-c);
        TS_ASSERT_THROWS_ANYTHING(c-a);

        TS_ASSERT_THROWS_ANYTHING(b-c);
        TS_ASSERT_THROWS_ANYTHING(c-b);
    }

    void testmatrix_negation_test () {
        Matrix a;
        std::stringstream("[1 2 -1 ; 0 -33 7]") >> a;
        Matrix b;
        b = -a;

        TS_ASSERT_EQUALS(b[0][0], -1);
        TS_ASSERT_EQUALS(b[0][1], -2);
        TS_ASSERT_EQUALS(b[0][2], 1);
        TS_ASSERT_EQUALS(b[1][0], 0);
        TS_ASSERT_EQUALS(b[1][1], 33);
        TS_ASSERT_EQUALS(b[1][2], -7);

        TS_ASSERT_EQUALS(a[0][0], 1);
        TS_ASSERT_EQUALS(a[0][1], 2);
        TS_ASSERT_EQUALS(a[0][2], -1);
        TS_ASSERT_EQUALS(a[1][0], 0);
        TS_ASSERT_EQUALS(a[1][1], -33);
        TS_ASSERT_EQUALS(a[1][2], 7);

    }

    void testmatrix_transpose_test () {
        Matrix a;
        std::stringstream("[1 2 3 ; 4 5 6]") >> a;
        Matrix b;
        b = a.transpose();

        // a unchanged
        TS_ASSERT_EQUALS(a[0][0], 1);
        TS_ASSERT_EQUALS(a[0][1], 2);
        TS_ASSERT_EQUALS(a[0][2], 3);
        TS_ASSERT_EQUALS(a[1][0], 4);
        TS_ASSERT_EQUALS(a[1][1], 5);
        TS_ASSERT_EQUALS(a[1][2], 6);


        // b == transpose(a)
        TS_ASSERT_EQUALS(b[0][0], 1);
        TS_ASSERT_EQUALS(b[0][1], 4);
        TS_ASSERT_EQUALS(b[1][0], 2);
        TS_ASSERT_EQUALS(b[1][1], 5);
        TS_ASSERT_EQUALS(b[2][0], 3);
        TS_ASSERT_EQUALS(b[2][1], 6);
    }

    // END OF OUR TESTS

};

#endif

