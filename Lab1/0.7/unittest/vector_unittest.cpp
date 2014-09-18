// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A sample program demonstrating using Google C++ testing framework.
//
// Author: wan@google.com (Zhanyong Wan)


// This sample shows how to write a simple unit test for a function,
// using Google C++ testing framework.
//
// Writing a unit test using Google C++ testing framework is easy as 1-2-3:


// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include "../Vector.h"
#include "../../gtest-1.7.0/include/gtest/gtest.h"

// Step 2. Use the TEST macro to define your tests.
//
// TEST has two parameters: the test case name and the test name.
// After using the macro, you should define your test logic between a
// pair of braces.  You can use a bunch of macros to indicate the
// success or failure of a test.  EXPECT_TRUE and EXPECT_EQ are
// examples of such macros.  For a complete list, see gtest.h.
//
// <TechnicalDetails>
//
// In Google Test, tests are grouped into test cases.  This is how we
// keep test code organized.  You should put logically related tests
// into the same test case.
//
// The test case name and the test name should both be valid C++
// identifiers.  And you should not use underscore (_) in the names.
//
// Google Test guarantees that each test you define is run exactly
// once, but it makes no guarantee on the order the tests are
// executed.  Therefore, you should write your tests in such a way
// that their results don't depend on their order.
//
// </TechnicalDetails>


// Test default constructor
TEST(default_constructor, size) {
	Vector<int> a;
	EXPECT_EQ(a.capacity(), 0);
}

// Test size of zero initialize constructor
TEST(zero_initialized_constructor, size) {
	Vector<int> a(0);
	EXPECT_EQ(a.capacity(), 0);

	Vector<int> b(3);
	EXPECT_EQ(b.capacity(), 3);

	Vector<int> c(10);
	EXPECT_EQ(c.capacity(), 10);
}

// Test size of zero initialize constructor
TEST(zero_initialized_constructor, int_content) {
  Vector<int> a(10);
}

// Test size of zero initialize constructor
TEST(change_content, int_content){
  Vector<int> a(2);
	size_t a_size = a.capacity();
  for (size_t i = 0; i < a_size; ++i) {
  	a[i] = 2;
  	EXPECT_EQ(a[i], 2);
  }
}

// Test size of zero initialize constructor
TEST(zero_initialized_constructor, float_content) {
  Vector<float> a(10);
}

// Dynamic allocation
// Test size of zero initialize constructor
TEST(dynamic_allocation, free_empty) {
  	Vector<int>* a = new Vector<int>(3);
    // a->print();
  	delete a;
}

TEST(dynamic_allocation, free_array) {
  Vector<int>* a = new Vector<int>[3];
  a[0] = Vector<int>(3);
  EXPECT_EQ(a[0].capacity(), 3);

  a[1] = Vector<int>(0);
  EXPECT_EQ(a[1].capacity(), 0);

  delete[] a;
}

TEST(num_elem_constructor_with_value, construct) {
  Vector<int>* a = new Vector<int>(10, 42);
  size_t size = a->capacity();
  EXPECT_EQ(size, 10);
  for (size_t i = 0; i < size; ++i){
    EXPECT_EQ((*a)[i], 42);
  }

  Vector<char> b(10, 'b');
  size = b.capacity();
  EXPECT_EQ(size, 10);
  for (size_t i = 0; i < size; ++i){
    EXPECT_EQ(b[i], 'b');
  }

  Vector<Vector<int>>* c = new Vector<Vector<int>>(10, *a);
  size = c->capacity();
  EXPECT_EQ(size, 10);
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < a->capacity(); ++j) {
      EXPECT_EQ((*c)[i][j], 42);
    }
  }
  delete a;
  delete c;
}

// Test capacity
TEST(capacity_test, size) {
  Vector<int> a;
  EXPECT_EQ(a.capacity(), 0);

  Vector<int> b(100);
  EXPECT_EQ(b.capacity(), 100);

}

// Test size
TEST(size_test, size) {
  Vector<int> a;
  EXPECT_EQ(a.size(), 0);

  Vector<int> b(100);
  EXPECT_EQ(b.size(), 100);

  //TODO: FIX MORE SIZE TESTS
}

// Test that begin() function returns pointer to first element in vector.
TEST(begin_function, correct_address) {
  Vector<int> a(10);
  EXPECT_EQ(a.begin(), &a[0]);
  *a.begin() = 2;
  EXPECT_EQ(a[0], 2);
}

// Test that begin() function returns pointer to first element in vector.
TEST(end_function, correct_address) {
  Vector<int> b(10);
  EXPECT_EQ(b.end(), &b[9] + 1);
}

// Test that the find(x) function returns pointer to first element that
// equals x. If no element matches, end() is return.
TEST(find_function, correct_address) {
  Vector<int> a{1,2,3,4,5,6};
  
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a.find(1), &a[0]);
  
  EXPECT_EQ(a[3], 4);
  EXPECT_EQ(a.find(4), &a[3]);

  EXPECT_EQ(a.find(9), &a[a.size()-1]+1);
}

// Test that push back functions correctly
// Counts with expand_factor = 2
TEST(push_back, correct_size) {
  Vector<int> a({1,2,3,4,5,6});
  EXPECT_EQ(a.size(), 6);
  a.push_back(7);
  EXPECT_EQ(a.size(), 7);
  a.push_back(8);
  EXPECT_EQ(a.size(), 8);
}

// Test that push back functions correctly
// Counts with expand_factor = 2
TEST(push_back, correct_capacity) {
  Vector<int> a({1,2});
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.capacity(), 2);
  a.push_back(3);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.capacity(), 6);
  a.push_back(4);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.capacity(), 6);
  a.push_back(5);
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.capacity(), 6);
}

// Test that expanding from 0-size container works properly
// Counts with expand_factor = 2
TEST(push_back, expand_from_0_container) {
  Vector<int> a;
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.capacity(), 0);
  a.push_back(1);
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(a.capacity(), 2);
}


// Test that the content when pushed is correct
TEST(push_back, content) {
  Vector<int> a;
  a.push_back(1);
  EXPECT_EQ(a[0], 1);
  a.push_back(2);
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 2);
  a.push_back(3);
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 3);
}

// TODO: Test is_move_constructible and is_move_assignable

