#include "../Matrix.h"
#include "../../gtest-1.7.0/include/gtest/gtest.h"
#include <string>


TEST(row_col_init, init_values) {
	Matrix a(2,3);
	EXPECT_EQ(a[0][0], 0);
	EXPECT_EQ(a[0][1], 0);
	EXPECT_EQ(a[0][2], 0);
	EXPECT_EQ(a[1][0], 0);
	EXPECT_EQ(a[1][1], 0);
	EXPECT_EQ(a[1][2], 0);
}

TEST(row_col_init, out_of_range_check) {
	Matrix a(2,3);
	EXPECT_NO_THROW(a[0][0]);
	EXPECT_NO_THROW(a[0][1]);
	EXPECT_NO_THROW(a[0][2]);
	EXPECT_NO_THROW(a[1][0]);
	EXPECT_NO_THROW(a[1][1]);
	EXPECT_NO_THROW(a[1][2]);
	EXPECT_THROW(a[2][0], std::out_of_range);
	EXPECT_THROW(a[0][3], std::out_of_range);
}

TEST(assignment, correct_values) {
	Matrix a(2,2);
	a[0][0] = 1;
	a[0][1] = 2;
	a[1][0] = 3;
	a[1][1] = 4;
	EXPECT_EQ(a[0][0], 1);
	EXPECT_EQ(a[0][1], 2);
	EXPECT_EQ(a[1][0], 3);
	EXPECT_EQ(a[1][1], 4);
}

TEST(identity, initiation) {
	Matrix a(1);
	EXPECT_EQ(a[0][0], 1);
	
	Matrix b(2);
	EXPECT_EQ(b[0][0], 1);
	EXPECT_EQ(b[0][1], 0);
	EXPECT_EQ(b[1][0], 0);
	EXPECT_EQ(b[1][1], 1);

	Matrix c(5);
	EXPECT_EQ(c[0][0], 1);
	EXPECT_EQ(c[0][1], 0);
	EXPECT_EQ(c[0][2], 0);
	EXPECT_EQ(c[0][3], 0);
	EXPECT_EQ(c[0][4], 0);
	EXPECT_EQ(c[1][0], 0);
	EXPECT_EQ(c[1][1], 1);
	EXPECT_EQ(c[1][2], 0);
	EXPECT_EQ(c[1][3], 0);
	EXPECT_EQ(c[1][4], 0);
	EXPECT_EQ(c[2][0], 0);
	EXPECT_EQ(c[2][1], 0);
	EXPECT_EQ(c[2][2], 1);
	EXPECT_EQ(c[2][3], 0);
	EXPECT_EQ(c[2][4], 0);
	EXPECT_EQ(c[3][0], 0);
	EXPECT_EQ(c[3][1], 0);
	EXPECT_EQ(c[3][2], 0);
	EXPECT_EQ(c[3][3], 1);
	EXPECT_EQ(c[3][4], 0);
	EXPECT_EQ(c[4][0], 0);
	EXPECT_EQ(c[4][1], 0);
	EXPECT_EQ(c[4][2], 0);
	EXPECT_EQ(c[4][3], 0);
	EXPECT_EQ(c[4][4], 1);
}

TEST(identity, out_of_range_check) {
	Matrix a(3);
	EXPECT_NO_THROW(a[0][0]);
	EXPECT_NO_THROW(a[0][1]);
	EXPECT_NO_THROW(a[0][2]);
	EXPECT_NO_THROW(a[1][0]);
	EXPECT_NO_THROW(a[1][1]);
	EXPECT_NO_THROW(a[1][2]);
	EXPECT_NO_THROW(a[2][0]);
	EXPECT_NO_THROW(a[2][1]);
	EXPECT_NO_THROW(a[2][2]);
	EXPECT_THROW(a[3][0], std::out_of_range);
	EXPECT_THROW(a[0][3], std::out_of_range);
}

TEST(input, to_empty_matrix) {
	Matrix a;
	std::stringstream ss("  [ 1 3 5 ; 0 2 0 ]");
	ss >> a;
	EXPECT_EQ(a[0][0], 1);
	EXPECT_EQ(a[0][1], 3);
	EXPECT_EQ(a[0][2], 5);
	EXPECT_EQ(a[1][0], 0);
	EXPECT_EQ(a[1][1], 2);
	EXPECT_EQ(a[1][2], 0);
}

TEST(input, to_larger_matrix) {
	Matrix a(4,4);
	std::stringstream ss("  [ 1 3 5 ; 0 2 0 ]");
	ss >> a;
	EXPECT_EQ(a[0][0], 1);
	EXPECT_EQ(a[0][1], 3);
	EXPECT_EQ(a[0][2], 5);
	EXPECT_EQ(a[1][0], 0);
	EXPECT_EQ(a[1][1], 2);
	EXPECT_EQ(a[1][2], 0);
	EXPECT_THROW(a[3][0], std::out_of_range);
	EXPECT_THROW(a[0][3], std::out_of_range);
}

TEST(input, to_smaller_matrix) {
	Matrix a(2,2);
	std::stringstream ss("  [ 1 3 5 ; 0 2 0 ]");
	ss >> a;
	EXPECT_EQ(a[0][0], 1);
	EXPECT_EQ(a[0][1], 3);
	EXPECT_EQ(a[0][2], 5);
	EXPECT_EQ(a[1][0], 0);
	EXPECT_EQ(a[1][1], 2);
	EXPECT_EQ(a[1][2], 0);
	EXPECT_THROW(a[3][0], std::out_of_range);
	EXPECT_THROW(a[0][3], std::out_of_range);
}

TEST(output, test) {
	Matrix a(3);
	Matrix b;
	std::stringstream ss;
	ss << a;
	ss >> b;
	EXPECT_EQ(b[0][0], a[0][0]);
	EXPECT_EQ(b[0][1], a[0][1]);
	EXPECT_EQ(b[0][2], a[0][2]);
	EXPECT_EQ(b[1][0], a[1][0]);
	EXPECT_EQ(b[1][1], a[1][1]);
	EXPECT_EQ(b[1][2], a[1][2]);
	EXPECT_EQ(b[2][0], a[2][0]);
	EXPECT_EQ(b[2][1], a[2][1]);
	EXPECT_EQ(b[2][2], a[2][2]);
}

TEST(scalar_mult, positive_scalar) {
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

	EXPECT_EQ(b[0][0], 0);
	EXPECT_EQ(b[0][1], 3);
	EXPECT_EQ(b[1][0], 6);
	EXPECT_EQ(b[1][1], 9);
	EXPECT_EQ(b[2][0], 12);
	EXPECT_EQ(b[2][1], 15);

	EXPECT_EQ(a[0][0], 0);
	EXPECT_EQ(a[0][1], 1);
	EXPECT_EQ(a[1][0], 2);
	EXPECT_EQ(a[1][1], 3);
	EXPECT_EQ(a[2][0], 4);
	EXPECT_EQ(a[2][1], 5);


	Matrix c;
	c = scalar * a;
	EXPECT_EQ(c[0][0], 0);
	EXPECT_EQ(c[0][1], 3);
	EXPECT_EQ(c[1][0], 6);
	EXPECT_EQ(c[1][1], 9);
	EXPECT_EQ(c[2][0], 12);
	EXPECT_EQ(c[2][1], 15);

	EXPECT_EQ(a[0][0], 0);
	EXPECT_EQ(a[0][1], 1);
	EXPECT_EQ(a[1][0], 2);
	EXPECT_EQ(a[1][1], 3);
	EXPECT_EQ(a[2][0], 4);
	EXPECT_EQ(a[2][1], 5);
}

TEST(scalar_mult, negative_scalar) {
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
	EXPECT_EQ(b[0][0], 0);
	EXPECT_EQ(b[0][1], -3);
	EXPECT_EQ(b[0][2], -6);
	EXPECT_EQ(b[1][0], -9);
	EXPECT_EQ(b[1][1], -12);
	EXPECT_EQ(b[1][2], -15);

	Matrix c;
	c = a * scalar;
	EXPECT_EQ(c[0][0], 0);
	EXPECT_EQ(c[0][1], -3);
	EXPECT_EQ(c[0][2], -6);
	EXPECT_EQ(c[1][0], -9);
	EXPECT_EQ(c[1][1], -12);
	EXPECT_EQ(c[1][2], -15);

	EXPECT_EQ(a[0][0], 0);
	EXPECT_EQ(a[0][1], 1);
	EXPECT_EQ(a[0][2], 2);
	EXPECT_EQ(a[1][0], 3);
	EXPECT_EQ(a[1][1], 4);
	EXPECT_EQ(a[1][2], 5);
}

TEST(scalar_mult, zero_scalar) {
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
	EXPECT_EQ(b[0][0], 0);
	EXPECT_EQ(b[0][1], 0);
	EXPECT_EQ(b[0][2], 0);
	EXPECT_EQ(b[1][0], 0);
	EXPECT_EQ(b[1][1], 0);
	EXPECT_EQ(b[1][2], 0);

	Matrix c;
	c = a * scalar;
	EXPECT_EQ(c[0][0], 0);
	EXPECT_EQ(c[0][1], 0);
	EXPECT_EQ(c[0][2], 0);
	EXPECT_EQ(c[1][0], 0);
	EXPECT_EQ(c[1][1], 0);
	EXPECT_EQ(c[1][2], 0);

	EXPECT_EQ(a[0][0], 0);
	EXPECT_EQ(a[0][1], 1);
	EXPECT_EQ(a[0][2], 2);
	EXPECT_EQ(a[1][0], 3);
	EXPECT_EQ(a[1][1], 4);
	EXPECT_EQ(a[1][2], 5);
}

TEST(scalar_mult, multiply_self) {
	Matrix a(2,3);
	a[0][0] = 0;
	a[0][1] = 1;
	a[0][2] = 2;
	a[1][0] = 3;
	a[1][1] = 4;
	a[1][2] = 5;

	int scalar = 3;
	a = a * scalar;
	EXPECT_EQ(a[0][0], 0);
	EXPECT_EQ(a[0][1], 3);
	EXPECT_EQ(a[0][2], 6);
	EXPECT_EQ(a[1][0], 9);
	EXPECT_EQ(a[1][1], 12);
	EXPECT_EQ(a[1][2], 15);
}

// TODO: CHECK IF THIS IS THE EXPECTED BEHAVIOUR
TEST(scalar_mult, size_zero) {
	Matrix a(0);
	int scalar = 3;
	a = a * scalar;
	EXPECT_THROW(a[0][0], std::out_of_range);
}

TEST(scalar_mult, size_one) {
	Matrix a(1);

	int scalar = 3;
	a = a * scalar;
	EXPECT_EQ(a[0][0], 3);
}

TEST(matrix_mult, test) {
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
	EXPECT_EQ(test1[0][0], 10);
	EXPECT_EQ(test1[0][1], 13);
	EXPECT_EQ(test1[1][0], 28);
	EXPECT_EQ(test1[1][1], 40);
	EXPECT_THROW(test1[0][2], std::out_of_range);
	EXPECT_THROW(test1[2][0], std::out_of_range);


	Matrix test2;
	test2 = b * a;
	EXPECT_EQ(test2[0][0], 3);
	EXPECT_EQ(test2[0][1], 4);
	EXPECT_EQ(test2[0][2], 5);
	EXPECT_EQ(test2[1][0], 9);
	EXPECT_EQ(test2[1][1], 14);
	EXPECT_EQ(test2[1][2], 19);
	EXPECT_EQ(test2[2][0], 15);
	EXPECT_EQ(test2[2][1], 24);
	EXPECT_EQ(test2[2][2], 33);
	EXPECT_THROW(test2[0][3], std::out_of_range);
	EXPECT_THROW(test2[3][0], std::out_of_range);
}

TEST(matrix_mult, non_compatible_sizes) {
	Matrix a(3,3);
	Matrix b(3,2);
	Matrix c(2,3);

	EXPECT_NO_THROW(a*b);
	EXPECT_THROW(b*a, std::invalid_argument);

	EXPECT_THROW(a*c, std::invalid_argument);
	EXPECT_NO_THROW(c*a);
}

// TODO: CHECK IF THIS IS THE EXPECTED BEHAVIOUR
TEST(matrix_mult, size_zero) {
	Matrix a(0);
	Matrix b(0);
	a = a * b;
	EXPECT_THROW(a[0][0], std::out_of_range);
}

TEST(matrix_mult, size_one) {
	Matrix a(1,1);
	Matrix b(1,1);
	a[0][0] = 2;
	b[0][0] = 4;

	a = a * b;
	EXPECT_EQ(a[0][0], 8);
	EXPECT_EQ(b[0][0], 4);

}

TEST(matrix_addition, test) {
	Matrix a;
	Matrix b;

	std::stringstream("[1 2 0 ; 9 8 7]") >> a;
	std::stringstream("[3 4 1 ; 9 1 7]") >> b;

	Matrix c;
	c = a + b;

	EXPECT_EQ(c[0][0], 4);
	EXPECT_EQ(c[0][1], 6);
	EXPECT_EQ(c[0][2], 1);
	EXPECT_EQ(c[1][0], 18);
	EXPECT_EQ(c[1][1], 9);
	EXPECT_EQ(c[1][2], 14);
}

TEST(matrix_addition, non_compatible_sizes) {
	Matrix a(3,3);
	Matrix b(3,2);
	Matrix c(2,3);

	EXPECT_THROW(a+b, std::invalid_argument);
	EXPECT_THROW(b+a, std::invalid_argument);

	EXPECT_THROW(a+c, std::invalid_argument);
	EXPECT_THROW(c+a, std::invalid_argument);

	EXPECT_THROW(b+c, std::invalid_argument);
	EXPECT_THROW(c+b, std::invalid_argument);
}

TEST(matrix_subtraction, test) {
	Matrix a;
	Matrix b;

	std::stringstream("[1 2 0 ; 9 8 7]") >> a;
	std::stringstream("[3 4 1 ; 9 1 7]") >> b;

	Matrix c;
	c = a - b;

	EXPECT_EQ(c[0][0], -2);
	EXPECT_EQ(c[0][1], -2);
	EXPECT_EQ(c[0][2], -1);
	EXPECT_EQ(c[1][0], 0);
	EXPECT_EQ(c[1][1], 7);
	EXPECT_EQ(c[1][2], 0);
}

TEST(matrix_subtraction, non_compatible_sizes) {
	Matrix a(3,3);
	Matrix b(3,2);
	Matrix c(2,3);

	EXPECT_THROW(a-b, std::invalid_argument);
	EXPECT_THROW(b-a, std::invalid_argument);

	EXPECT_THROW(a-c, std::invalid_argument);
	EXPECT_THROW(c-a, std::invalid_argument);

	EXPECT_THROW(b-c, std::invalid_argument);
	EXPECT_THROW(c-b, std::invalid_argument);
}

TEST(matrix_negation, test) {
	Matrix a;
	std::stringstream("[1 2 -1 ; 0 -33 7]") >> a;
	Matrix b;
	b = -a;

	EXPECT_EQ(b[0][0], -1);
	EXPECT_EQ(b[0][1], -2);
	EXPECT_EQ(b[0][2], 1);
	EXPECT_EQ(b[1][0], 0);
	EXPECT_EQ(b[1][1], 33);
	EXPECT_EQ(b[1][2], -7);

	EXPECT_EQ(a[0][0], 1);
	EXPECT_EQ(a[0][1], 2);
	EXPECT_EQ(a[0][2], -1);
	EXPECT_EQ(a[1][0], 0);
	EXPECT_EQ(a[1][1], -33);
	EXPECT_EQ(a[1][2], 7);

}

TEST(matrix_transpose, test) {
	Matrix a;
	std::stringstream("[1 2 3 ; 4 5 6]") >> a;
	Matrix b;
	b = a.transpose();

	// a changed
	EXPECT_EQ(a[0][0], 1);
	EXPECT_EQ(a[0][1], 4);
	EXPECT_EQ(a[1][0], 2);
	EXPECT_EQ(a[1][1], 5);
	EXPECT_EQ(a[2][0], 3);
	EXPECT_EQ(a[2][1], 6);


	// b == transpose(a)
	EXPECT_EQ(b[0][0], 1);
	EXPECT_EQ(b[0][1], 4);
	EXPECT_EQ(b[1][0], 2);
	EXPECT_EQ(b[1][1], 5);
	EXPECT_EQ(b[2][0], 3);
	EXPECT_EQ(b[2][1], 6);
}

TEST(index_operator, index_out_of_bounds_check) {
	// TODO
}

