#include "../Gregorian.h"
#include "../../gtest-1.7.0/include/gtest/gtest.h"


TEST(row_col_init, init_values) {
	lab2::Gregorian a(1,2,3);
	EXPECT_EQ(a.day(), 1);
	EXPECT_EQ(a.days_per_week(), 7);
}

