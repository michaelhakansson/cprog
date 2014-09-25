#include "../Vector.h"
#include "../../gtest-1.7.0/include/gtest/gtest.h"
#include <string>

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

// Test that end() function returns pointer to first element in vector.
TEST(end_function, correct_address) {
  Vector<int> b(10);
  EXPECT_EQ(b.end(), &b[9] + 1);
}

// Test that begin() and end() function returns the same pointer when
// invoked on a empty vector.
TEST(begin_end, same_address) {
  Vector<int> a;
  EXPECT_EQ(a.begin(), a.end());
  a.push_back(123);
  EXPECT_NE(a.begin(), a.end());
}

// Test that the find(x) function returns pointer to first element that
// equals x. If no element matches, end() is return.
TEST(find_function, correct_address) {
  Vector<int> a{1,2,3,4,5,6};
  
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a.find(1), &a[0]);
  
  EXPECT_EQ(a[3], 4);
  EXPECT_EQ(a.find(4), &a[3]);

  // Does not exist
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
  EXPECT_EQ(a.capacity(), 4);
  a.push_back(4);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.capacity(), 4);
  a.push_back(5);
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.capacity(), 8);
}

// Test that expanding from 0-size container works properly
// Counts with expand_factor = 2
TEST(push_back, expand_from_0_container) {
  Vector<int> a;
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.capacity(), 0);
  a.push_back(1);
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(a.capacity(), 1);
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

TEST(clear, will_clear_vector) {
  Vector<int> a{1,2,3};
  EXPECT_EQ(a.size(), 3);
  a.clear();
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.capacity(), 3);
  EXPECT_EQ(a.begin(), a.end());
}

TEST(erase, erase_first) {
  Vector<int> a{1,2,3,4,5};
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.capacity(), 5);
  a.erase(0);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.capacity(), 5);
  EXPECT_EQ(a[0], 2);
  EXPECT_EQ(a[1], 3);
  EXPECT_EQ(a[2], 4);
  EXPECT_EQ(a[3], 5);
}

TEST(erase, erase_last) {
  Vector<int> a{1,2,3,4,5};
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.capacity(), 5);
  a.erase(4);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.capacity(), 5);
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 3);
  EXPECT_EQ(a[3], 4);
}

TEST(erase, erase_and_collapse) {
  Vector<int> a{1,2,3,4,5};
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.capacity(), 5);
  a.erase(3);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(a.capacity(), 5);
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 3);
  EXPECT_EQ(a[3], 5);
}

TEST(erase, erase_only_element) {
  Vector<int> a{1};
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(a.capacity(), 1);
  a.erase(0);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.capacity(), 1);
  EXPECT_EQ(a.begin(), a.end());
}

TEST(insert, size_capacity) {
  Vector<int> a;
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.capacity(), 0);
  a.insert(0, 123);
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(a.capacity(), 1);
  a.insert(1, 321);
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.capacity(), 2);
}

TEST(insert, empty_vector) {
  Vector<int> a;
  a.insert(0, 123);
  EXPECT_EQ(a[0], 123);
}

TEST(insert, element_first) {
  Vector<int> a{1};
  a.insert(0, 123);
  EXPECT_EQ(a[0], 123);
  EXPECT_EQ(a[1], 1);
}

TEST(insert, element_middle) {
  Vector<int> a{1,2};
  a.insert(1, 123);
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 123);
  EXPECT_EQ(a[2], 2);
  a.insert(1, 345);
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 345);
  EXPECT_EQ(a[2], 123);
  EXPECT_EQ(a[3], 2);
}

TEST(insert, element_last) {
  Vector<int> a{1};
  a.insert(1, 123);
  a.insert(2, 234);
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 123);
  EXPECT_EQ(a[2], 234);
}

TEST(insert, element_last_multiple_times) {
  Vector<int> a;
  a.insert(0, 123);
  a.insert(1, 456);
  a.insert(2, 789);
  EXPECT_EQ(a[0], 123);
  EXPECT_EQ(a[1], 456);
  EXPECT_EQ(a[2], 789);
}

TEST(insert, element_first_multiple_times) {
  Vector<int> a;
  a.insert(0, 123);
  a.insert(0, 456);
  a.insert(0, 789);
  EXPECT_EQ(a[0], 789);
  EXPECT_EQ(a[1], 456);
  EXPECT_EQ(a[2], 123);
}

TEST(insert, string) {
  Vector<std::string> a;
  a.insert(0, "ghi");
  a.insert(0, "def");
  a.insert(0, "abc");
  EXPECT_EQ(a[0], "abc");
  EXPECT_EQ(a[1], "def");
  EXPECT_EQ(a[2], "ghi");
}

// KATTIS VILLE ATT ERASE SKULLE KASTA EXCEPTION
TEST(kattis, test8) {
  Vector<int> vec(1000, 1024);
  vec.push_back(2048);
  EXPECT_GE(vec.capacity(), 1001);
  vec.insert(0, 123);
  vec.insert(2, 1337);
  vec.insert(5, 123);
  EXPECT_EQ(*(vec.end()-1), 2048);
  EXPECT_EQ(*(vec.begin()), 123);
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
  // EXPECT_EQ(*(vec.begin()), 123);
  // Non existing element searched ==> Return end pointer
  EXPECT_EQ(vec.end(), vec.find(1337));
  // vec.erase(2);
}

TEST(kattis, test11) {
  Vector<int> A{1,2,3};
  Vector<int> B(10);
  EXPECT_EQ(A.size(), 3);
  Vector<int> C(0);
    EXPECT_EQ(B.size(), 10);
    EXPECT_EQ(C.size(), 0);
  C = A;
  A = B;
  Vector<int> D(C); // 6: SKA VARA C = D?
  EXPECT_EQ(A.size(), 10);
  EXPECT_EQ(B.size(), 10);
  EXPECT_EQ(C.size(), 3);
  EXPECT_EQ(C.size(), 3);
  A[1] = 10;
  B[2] = 11;
  B.erase(0);
  EXPECT_THROW(C[3] = 12, std::out_of_range);
  C.erase(1);
  EXPECT_EQ(A[1], 10);
  EXPECT_EQ(B[2], 0);
  EXPECT_THROW(C[3], std::out_of_range);
  A.clear(); // 18: RESET $A?
  EXPECT_EQ(A.size(), 0);
  C = std::move(A);
  A.clear();
  EXPECT_THROW(C[3], std::out_of_range);
  EXPECT_THROW(C[3] = 25, std::out_of_range);
  A = std::move(C);
  A = B;
}


// TODO: Test is_move_constructible and is_move_assignable

