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

#include "../UIntVector.h"
#include <gtest/gtest.h> // Use row below instead if you don't have gtest in your global include path
//#include "../../gtest-1.7.0/include/gtest/gtest.h"

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


// Test size of zero initialize constructor
TEST(ZeroInitializeConstructor, Size) {
	UIntVector a(2);
	a[1] = 2;
  	EXPECT_EQ(a.size(), 2);
  	UIntVector b(0);
  	EXPECT_EQ(b.size(), 0);
}

// Test content of zero initialize constructor
TEST(ZeroInitializeConstructor, Content) {
	size_t size = 10;
	UIntVector a(size);
	for(size_t i = 0; i < size; ++i) {
		EXPECT_EQ(a[i], 0);
	}
}

// Test operator[]
TEST(BracketOperator, out_of_range) {
	UIntVector a(10);
	EXPECT_NO_THROW(a[0]);
	EXPECT_NO_THROW(a[1]);
	EXPECT_NO_THROW(a[9]);
	EXPECT_THROW(a[10], std::out_of_range);
}

// Test size()
TEST(size_function, size) {
	UIntVector e(0);
	EXPECT_EQ(e.size(), 0);
	UIntVector d(1);
	EXPECT_EQ(d.size(), 1);
	UIntVector c(2);
	EXPECT_EQ(c.size(), 2);
	UIntVector b(5);
	EXPECT_EQ(b.size(), 5);
	UIntVector a(100);
	EXPECT_EQ(a.size(), 100);
}

// Test reset()
TEST(reset_fuction, reset) {
	UIntVector a{0,1,2,3,4,5};
	size_t size = a.size();
	for(size_t i = 0; i < size; ++i) {
		EXPECT_EQ(a[i], i);
	}
	a.reset();
	for(size_t i = 0; i < size; ++i) {
		EXPECT_EQ(a[i], 0);
	}
	EXPECT_EQ(a.size(), size);
}

// Test reset()
TEST(dynamic_allocation, destruct) {
	UIntVector *a = new UIntVector(2);
	a->print();
	delete a;
}

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?
