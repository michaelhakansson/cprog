#include "../../gtest-1.7.0/include/gtest/gtest.h"
#include "../gregorian.h"
#include <iostream>
#include <string>

using namespace lab2;

TEST(Gregorian, default_constructor) {
	time_t tp;
	time(&tp);
	set_k_time(tp);

    struct tm *t = gmtime(&tp);
    int year  = t->tm_year + 1900;
    int month = t->tm_mon + 1;      // månaderna och dagarna
    int day   = t->tm_mday;         // indexerade från ETT

	Gregorian g;
	EXPECT_EQ(g.day(), day);
	EXPECT_EQ(g.month(), month);
	EXPECT_EQ(g.year(), year);
	EXPECT_EQ(g.days_per_week(), 7);
}

TEST(Gregorian, explicit_constructor) {
	Gregorian g(13,3,2001);
	EXPECT_EQ(g.day(), 13);
	EXPECT_EQ(g.month(), 3);
	EXPECT_EQ(g.year(), 2001);
}

TEST(Gregorian, output_test) {
	Gregorian g1(1,1,2000);
	Gregorian g2(22,11,1921);
	Gregorian g3(22,11,8);
	
	std::stringstream ss1;
	ss1 << g1;
	std::string wanted = "2000-01-01";
	std::string output = ss1.str();
	EXPECT_EQ(wanted, output);

	std::stringstream ss2;
	ss2 << g2;
	wanted = "1921-11-22";
	output = ss2.str();
	EXPECT_EQ(wanted, output);
	
	std::stringstream ss3;
	ss3 << g3;
	wanted = "8-11-22";
	output = ss3.str();
	EXPECT_EQ(wanted, output);
}

// Commented away since leap year function is now declared private
// TEST(Gregorian, leap_years) {
// 	Gregorian g1(22,1,2000);
// 	EXPECT_EQ(g1.leap_year(), true);

// 	Gregorian g2(22,1,1900);
// 	EXPECT_EQ(g2.leap_year(), false);

// 	Gregorian g3(22,1,2001);
// 	EXPECT_EQ(g3.leap_year(), false);
// }

TEST(Gregorian, days_this_month) {
	Gregorian g1(22,1,1921);
	Gregorian g2(22,2,1921); // February NOT leap year
	Gregorian g_leap_year(1,2,2000); // February leap year
	Gregorian g3(22,3,1921);
	Gregorian g4(22,4,1921);
	Gregorian g5(22,5,1921);
	Gregorian g6(22,6,1921);
	Gregorian g7(22,7,1921);
	Gregorian g8(22,8,1921);
	Gregorian g9(22,9,1921);
	Gregorian g10(22,10,1921);
	Gregorian g11(22,11,1921);
	Gregorian g12(22,12,1921);


	EXPECT_EQ(g1.days_this_month(), 31);
	EXPECT_EQ(g2.days_this_month(), 28); // Not leap year
	EXPECT_EQ(g_leap_year.days_this_month(), 29); // Leap year
	EXPECT_EQ(g3.days_this_month(), 31);
	EXPECT_EQ(g4.days_this_month(), 30);
	EXPECT_EQ(g5.days_this_month(), 31);
	EXPECT_EQ(g6.days_this_month(), 30);
	EXPECT_EQ(g7.days_this_month(), 31);
	EXPECT_EQ(g8.days_this_month(), 31);
	EXPECT_EQ(g9.days_this_month(), 30);
	EXPECT_EQ(g10.days_this_month(), 31);
	EXPECT_EQ(g11.days_this_month(), 30);
	EXPECT_EQ(g12.days_this_month(), 31);
}

TEST(Gregorian, julian_day_number) {
	Gregorian g1(16,11,1858);
	Gregorian g2(17,11,1858);
	Gregorian g3(18,11,1858);
	Gregorian g4(12,3,2014);

	EXPECT_EQ(g1.mod_julian_day(), -1);
	EXPECT_EQ(g2.mod_julian_day(),  0);
	EXPECT_EQ(g3.mod_julian_day(),  1);
	EXPECT_EQ(g4.mod_julian_day(),  56728);

}

TEST(Gregorian, week_day_number) {
	Gregorian g1(30,10,2014);
	Gregorian g2(31,10,2014);
	Gregorian g3(31,10,2006);
	Gregorian g4(29,10,2006);
	Gregorian g5(30,10,2006);
	EXPECT_EQ(g1.week_day(), 4);
	EXPECT_EQ(g2.week_day(), 5);
	EXPECT_EQ(g3.week_day(), 2);
	EXPECT_EQ(g4.week_day(), 7);
	EXPECT_EQ(g5.week_day(), 1);
}

TEST(Gregorian, week_day_name) {
	Gregorian g1(30,10,2014);
	Gregorian g2(31,10,2014);
	Gregorian g3(31,10,2006);
	Gregorian g4(29,10,2006);
	Gregorian g5(30,10,2006);
	EXPECT_EQ(g1.week_day_name(), "thursday");
	EXPECT_EQ(g2.week_day_name(), "friday");
	EXPECT_EQ(g3.week_day_name(), "tuesday");
	EXPECT_EQ(g4.week_day_name(), "sunday");
	EXPECT_EQ(g5.week_day_name(), "monday");
}

TEST(Gregorian, month_names) {
	Gregorian g1(30,1,2014);
	Gregorian g2(28,2,2014);
	Gregorian g3(31,10,2006);
	Gregorian g4(29,11,2006);
	Gregorian g5(30,12,2006);
	EXPECT_EQ(g1.month_name(), "january");
	EXPECT_EQ(g2.month_name(), "february");
	EXPECT_EQ(g3.month_name(), "october");
	EXPECT_EQ(g4.month_name(), "november");
	EXPECT_EQ(g5.month_name(), "december");
}

TEST(Gregorian, increment_operator) {
	Gregorian g1(30,12,2014);

	EXPECT_EQ(g1.day(), 30);
	EXPECT_EQ(g1.month(), 12);
	EXPECT_EQ(g1.year(), 2014);
	++g1;

	EXPECT_EQ(g1.day(), 31);
	EXPECT_EQ(g1.month(), 12);
	EXPECT_EQ(g1.year(), 2014);
	++g1;

	EXPECT_EQ(g1.day(), 1);
	EXPECT_EQ(g1.month(), 1);
	EXPECT_EQ(g1.year(), 2015);

	// A leap year
	Gregorian g2(28,2,2000);
	EXPECT_EQ(g2.day(), 28);
	EXPECT_EQ(g2.month(), 2);
	EXPECT_EQ(g2.year(), 2000);
	++g2;

	EXPECT_EQ(g2.day(), 29);
	EXPECT_EQ(g2.month(), 2);
	EXPECT_EQ(g2.year(), 2000);
	++g2;

	EXPECT_EQ(g2.day(), 1);
	EXPECT_EQ(g2.month(), 3);
	EXPECT_EQ(g2.year(), 2000);

	// NOT a leap year
	Gregorian g3(28,2,2001);
	EXPECT_EQ(g3.day(), 28);
	EXPECT_EQ(g3.month(), 2);
	EXPECT_EQ(g3.year(), 2001);
	++g3;

	EXPECT_EQ(g3.day(), 1);
	EXPECT_EQ(g3.month(), 3);
	EXPECT_EQ(g3.year(), 2001);

	Date& g4 = ++g3;
	EXPECT_EQ(g3.day(), 2);
	EXPECT_EQ(g3.month(), 3);
	EXPECT_EQ(g3.year(), 2001);
	EXPECT_EQ(g4.day(), 2);
	EXPECT_EQ(g4.month(), 3);
	EXPECT_EQ(g4.year(), 2001);
}

TEST(Gregorian, decrement_operator) {
	Gregorian g1(1,1,2014);

	EXPECT_EQ(g1.day(), 1);
	EXPECT_EQ(g1.month(), 1);
	EXPECT_EQ(g1.year(), 2014);
	--g1;

	EXPECT_EQ(g1.day(), 31);
	EXPECT_EQ(g1.month(), 12);
	EXPECT_EQ(g1.year(), 2013);
	--g1;

	EXPECT_EQ(g1.day(), 30);
	EXPECT_EQ(g1.month(), 12);
	EXPECT_EQ(g1.year(), 2013);

	// A leap year
	Gregorian g2(1,3,2000);
	EXPECT_EQ(g2.day(), 1);
	EXPECT_EQ(g2.month(), 3);
	EXPECT_EQ(g2.year(), 2000);
	--g2;

	EXPECT_EQ(g2.day(), 29);
	EXPECT_EQ(g2.month(), 2);
	EXPECT_EQ(g2.year(), 2000);
	--g2;

	EXPECT_EQ(g2.day(), 28);
	EXPECT_EQ(g2.month(), 2);
	EXPECT_EQ(g2.year(), 2000);

	// NOT a leap year
	Gregorian g3(1,3,2001);
	EXPECT_EQ(g3.day(), 1);
	EXPECT_EQ(g3.month(), 3);
	EXPECT_EQ(g3.year(), 2001);
	--g3;

	EXPECT_EQ(g3.day(), 28);
	EXPECT_EQ(g3.month(), 2);
	EXPECT_EQ(g3.year(), 2001);

	Date& g4 = --g3;
	EXPECT_EQ(g3.day(), 27);
	EXPECT_EQ(g3.month(), 2);
	EXPECT_EQ(g3.year(), 2001);
	EXPECT_EQ(g4.day(), 27);
	EXPECT_EQ(g4.month(), 2);
	EXPECT_EQ(g4.year(), 2001);
}

TEST(Gregorian, minus_equals) {
	Gregorian g1(30,1,2014);
	g1 -= 3;
	EXPECT_EQ(g1.day(), 27);
	EXPECT_EQ(g1.month(), 1);
	EXPECT_EQ(g1.year(), 2014);

	g1 -= 27;
	EXPECT_EQ(g1.day(), 31);
	EXPECT_EQ(g1.month(), 12);
	EXPECT_EQ(g1.year(), 2013);
}

TEST(Gregorian, plus_equals) {
	Gregorian g1(30,1,2014);
	g1 += 3;
	EXPECT_EQ(g1.day(), 2);
	EXPECT_EQ(g1.month(), 2);
	EXPECT_EQ(g1.year(), 2014);

	g1 += 27;
	EXPECT_EQ(g1.day(), 1);
	EXPECT_EQ(g1.month(), 3);
	EXPECT_EQ(g1.year(), 2014);
}

TEST(Gregorian, equals) {
	Gregorian g1(30,1,2014);
	Gregorian g2(30,1,2014);
	Gregorian g3(31,1,2014);

	EXPECT_TRUE(g1 == g2);
	EXPECT_FALSE(g1 == g3);
}

TEST(Gregorian, not_equals) {
	Gregorian g1(30,1,2014);
	Gregorian g2(30,1,2014);
	Gregorian g3(31,1,2014);

	EXPECT_FALSE(g1 != g2);
	EXPECT_TRUE(g1 != g3);
}

TEST(Gregorian, less) {
	Gregorian g1(29,1,2014);
	Gregorian g2(30,1,2014);

	EXPECT_FALSE(g2 < g1);
	EXPECT_TRUE(g1 < g2);
}

TEST(Gregorian, less_equals) {
	Gregorian g1(29,1,2014);
	Gregorian g2(30,1,2014);

	EXPECT_FALSE(g2 <= g1);
	EXPECT_TRUE(g1 <= g2);
	EXPECT_TRUE(g2 <= g2);
}

TEST(Gregorian, greater) {
	Gregorian g1(29,1,2014);
	Gregorian g2(30,1,2014);

	EXPECT_FALSE(g1 > g2);
	EXPECT_TRUE(g2 > g1);
}

TEST(Gregorian, greater_equals) {
	Gregorian g1(29,1,2014);
	Gregorian g2(30,1,2014);

	EXPECT_FALSE(g1 >= g2);
	EXPECT_TRUE(g2 >= g1);
	EXPECT_TRUE(g2 >= g2);
}

TEST(Gregorian, minus) {
	Gregorian g1(1,1,2014);
	Gregorian g2(30,1,2014);

	EXPECT_EQ(g1-g1, 0);
	EXPECT_EQ(g2-g2, 0);
	EXPECT_EQ(g1-g2, -29);
	EXPECT_EQ(g2-g1, 29);
}

TEST(Gregorian, throw_on_unvalid_date) {
	EXPECT_NO_THROW(Gregorian a(1,1,2014));
	EXPECT_NO_THROW(Gregorian a(29,2,2000));
	EXPECT_NO_THROW(Gregorian a(31,1,2000));
	EXPECT_THROW(Gregorian a(29,2,2001), std::out_of_range);
}

TEST(Gregorian, copy_constructor) {
	Gregorian a(1,1,2014);
	Gregorian b = a;
	EXPECT_EQ(a, b);
	EXPECT_EQ(a-b, 0);
	EXPECT_EQ(b-a, 0);
}

TEST(Gregorian, add_year) {
	Gregorian leap(29,2,2000);
	leap.add_year();
	EXPECT_EQ(leap.year(), 2001);
	EXPECT_EQ(leap.month(), 2);
	EXPECT_EQ(leap.day(), 28);

	leap.add_year(-1);
	EXPECT_EQ(leap.year(), 2000);
	EXPECT_EQ(leap.month(), 2);
	EXPECT_EQ(leap.day(), 28);

	leap.add_year(1);
	EXPECT_EQ(leap.year(), 2001);
	EXPECT_EQ(leap.month(), 2);
	EXPECT_EQ(leap.day(), 28);

	Gregorian leap2(29,2,2000);
	leap2.add_year(4);
	EXPECT_EQ(leap2.year(), 2004);
	EXPECT_EQ(leap2.month(), 2);
	EXPECT_EQ(leap2.day(), 29);
}

TEST(Gregorian, add_month) {
	Gregorian g1(1,9,2014);
	g1.add_month();
	EXPECT_EQ(g1.year(), 2014);
	EXPECT_EQ(g1.month(), 10);
	EXPECT_EQ(g1.day(), 1);

	Gregorian g2(31,3,2014);
	g2.add_month();
	EXPECT_EQ(g2.year(), 2014);
	EXPECT_EQ(g2.month(), 4);
	EXPECT_EQ(g2.day(), 30);

	Gregorian leap(31,1,2000);
	leap.add_month();
	EXPECT_EQ(leap.year(), 2000);
	EXPECT_EQ(leap.month(), 3);
	EXPECT_EQ(leap.day(), 1);

	Gregorian not_leap(31,1,2001);
	not_leap.add_month();
	EXPECT_EQ(not_leap.year(), 2001);
	EXPECT_EQ(not_leap.month(), 3);
	EXPECT_EQ(not_leap.day(), 2);

	Gregorian g3(31,1,2001);
	Gregorian g4(31,1,2001);
	g3.add_month();
	g3.add_month();
	g3.add_month();
	g3.add_month();
	g3.add_month();
	g4.add_month(5);
	EXPECT_TRUE(g3==g4);
	EXPECT_TRUE(g3-g4 == 0);
	EXPECT_TRUE(g4-g3 == 0);


}
