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
	Gregorian g(2001,3,13);
	EXPECT_EQ(g.day(), 13);
	EXPECT_EQ(g.month(), 3);
	EXPECT_EQ(g.year(), 2001);
}

TEST(Gregorian, output_test) {
	Gregorian g1(2000,1,1);
	Gregorian g2(1921,11,22);
	Gregorian g3(8,11,22);
	
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

// //Commented away since leap year function is now declared private
// TEST(Gregorian, leap_years) {
// 	Gregorian g1(2000,1,22);
// 	EXPECT_EQ(g1.leap_year(), true);

// 	Gregorian g2(1900,1,22);
// 	EXPECT_EQ(g2.leap_year(), false);

// 	Gregorian g3(2001,1,22);
// 	EXPECT_EQ(g3.leap_year(), false);
// }

TEST(Gregorian, days_this_month) {
	Gregorian g1(1921,1,22);
	Gregorian g2(1921,2,22); // February NOT leap year
	Gregorian g_leap_year(2000,2,1); // February leap year
	Gregorian g3(1921,3,22);
	Gregorian g4(1921,4,22);
	Gregorian g5(1921,5,22);
	Gregorian g6(1921,6,22);
	Gregorian g7(1921,7,22);
	Gregorian g8(1921,8,22);
	Gregorian g9(1921,9,22);
	Gregorian g10(1921,10,22);
	Gregorian g11(1921,11,22);
	Gregorian g12(1921,12,22);


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
	Gregorian g1(1858,11,16);
	Gregorian g2(1858,11,17);
	Gregorian g3(1858,11,18);
	Gregorian g4(2014,3,12);

	EXPECT_EQ(g1.mod_julian_day(), -1);
	EXPECT_EQ(g2.mod_julian_day(),  0);
	EXPECT_EQ(g3.mod_julian_day(),  1);
	EXPECT_EQ(g4.mod_julian_day(),  56728);
}

TEST(Gregorian, week_day_number) {
	Gregorian g1(2014,10,30);
	Gregorian g2(2014,10,31);
	Gregorian g3(2006,10,31);
	Gregorian g4(2006,10,29);
	Gregorian g5(2006,10,31);
	EXPECT_EQ(g1.week_day(), 4);
	EXPECT_EQ(g2.week_day(), 5);
	EXPECT_EQ(g3.week_day(), 2);
	EXPECT_EQ(g4.week_day(), 7);
	EXPECT_EQ(g5.week_day(), 2);
}

TEST(Gregorian, week_day_name) {
	Gregorian g1(2014,10,30);
	Gregorian g2(2014,10,31);
	Gregorian g3(2006,10,31);
	Gregorian g4(2006,10,29);
	Gregorian g5(2006,10,30);
	EXPECT_EQ(g1.week_day_name(), "thursday");
	EXPECT_EQ(g2.week_day_name(), "friday");
	EXPECT_EQ(g3.week_day_name(), "tuesday");
	EXPECT_EQ(g4.week_day_name(), "sunday");
	EXPECT_EQ(g5.week_day_name(), "monday");
}

TEST(Gregorian, month_names) {
	Gregorian g1(2014,1,30);
	Gregorian g2(2014,2,28);
	Gregorian g3(2006,10,31);
	Gregorian g4(2006,11,29);
	Gregorian g5(2006,12,30);
	EXPECT_EQ(g1.month_name(), "january");
	EXPECT_EQ(g2.month_name(), "february");
	EXPECT_EQ(g3.month_name(), "october");
	EXPECT_EQ(g4.month_name(), "november");
	EXPECT_EQ(g5.month_name(), "december");
}

TEST(Gregorian, increment_operator) {
	Gregorian g1(2014,12,30);

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
	Gregorian g2(2000,2,28);
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
	Gregorian g3(2001,2,28);
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
	Gregorian g1(2014,1,1);

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
	Gregorian g2(2000,3,1);
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
	Gregorian g3(2001,3,1);
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
	Gregorian g1(2014,1,30);
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
	Gregorian g1(2014,1,30);
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
	Gregorian g1(2014,1,30);
	Gregorian g2(2014,1,30);
	Gregorian g3(2014,1,31);

	EXPECT_TRUE(g1 == g2);
	EXPECT_FALSE(g1 == g3);
}

TEST(Gregorian, not_equals) {
	Gregorian g1(2014,1,30);
	Gregorian g2(2014,1,30);
	Gregorian g3(2014,1,31);

	EXPECT_FALSE(g1 != g2);
	EXPECT_TRUE(g1 != g3);
}

TEST(Gregorian, less) {
	Gregorian g1(2014,1,29);
	Gregorian g2(2014,1,30);

	EXPECT_FALSE(g2 < g1);
	EXPECT_TRUE(g1 < g2);
}

TEST(Gregorian, less_equals) {
	Gregorian g1(2014,1,29);
	Gregorian g2(2014,1,30);

	EXPECT_FALSE(g2 <= g1);
	EXPECT_TRUE(g1 <= g2);
	EXPECT_TRUE(g2 <= g2);
}

TEST(Gregorian, greater) {
	Gregorian g1(2014,1,29);
	Gregorian g2(2014,1,30);

	EXPECT_FALSE(g1 > g2);
	EXPECT_TRUE(g2 > g1);
}

TEST(Gregorian, greater_equals) {
	Gregorian g1(2014,1,29);
	Gregorian g2(2014,1,30);

	EXPECT_FALSE(g1 >= g2);
	EXPECT_TRUE(g2 >= g1);
	EXPECT_TRUE(g2 >= g2);
}

TEST(Gregorian, minus) {
	Gregorian g1(2014,1,1);
	Gregorian g2(2014,1,30);

	EXPECT_EQ(g1-g1, 0);
	EXPECT_EQ(g2-g2, 0);
	EXPECT_EQ(g1-g2, -29);
	EXPECT_EQ(g2-g1, 29);
}

TEST(Gregorian, throw_on_unvalid_date) {
	EXPECT_NO_THROW(Gregorian a(2014,1,1));
	EXPECT_NO_THROW(Gregorian a(2000,2,29));
	EXPECT_NO_THROW(Gregorian a(2000,1,31));
	EXPECT_THROW(Gregorian a(2001,2,29), std::out_of_range);
}

TEST(Gregorian, copy_constructor) {
	Gregorian a(2014,1,1);
	Gregorian b = a;
	EXPECT_EQ(a, b);
	EXPECT_EQ(a-b, 0);
	EXPECT_EQ(b-a, 0);

	Date& c = b;
	EXPECT_EQ(c.month(), a.month());
	EXPECT_EQ(c.day(), a.day());
	EXPECT_EQ(c.year(), a.year());
}

TEST(Gregorian, add_year) {
	Gregorian leap(2000,2,29);
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

	Gregorian leap2(2000,2,29);
	leap2.add_year(4);
	EXPECT_EQ(leap2.year(), 2004);
	EXPECT_EQ(leap2.month(), 2);
	EXPECT_EQ(leap2.day(), 29);
}

TEST(Gregorian, add_month) {
	Gregorian g1(2014,9,1);
	g1.add_month();
	EXPECT_EQ(g1.year(), 2014);
	EXPECT_EQ(g1.month(), 10);
	EXPECT_EQ(g1.day(), 1);

	Gregorian g2(2014,3,31);
	g2.add_month();
	EXPECT_EQ(g2.year(), 2014);
	EXPECT_EQ(g2.month(), 4);
	EXPECT_EQ(g2.day(), 30);

	Gregorian leap(2000,1,31);
	leap.add_month();
	EXPECT_EQ(leap.year(), 2000);
	EXPECT_EQ(leap.month(), 3);
	EXPECT_EQ(leap.day(), 1);

	Gregorian not_leap(2001,1,31);
	not_leap.add_month();
	EXPECT_EQ(not_leap.year(), 2001);
	EXPECT_EQ(not_leap.month(), 3);
	EXPECT_EQ(not_leap.day(), 2);

	Gregorian g3(2001,1,31);
	Gregorian g4(2001,1,31);
	g3.add_month();
	g3.add_month();
	g3.add_month();
	g3.add_month();
	g3.add_month();
	g4.add_month(5);
	EXPECT_TRUE(g3==g4);
	EXPECT_TRUE(g3-g4 == 0);
	EXPECT_TRUE(g4-g3 == 0);

	g3.add_month(-1);
	g3.add_month(-1);
	g3.add_month(-1);
	g3.add_month(-1);
	g3.add_month(-1);
	g4.add_month(-5);
	EXPECT_TRUE(g3==g4);
	EXPECT_TRUE(g3-g4 == 0);
	EXPECT_TRUE(g4-g3 == 0);

	Gregorian g5(2014,10,31);
	g5.add_month(-1);
	EXPECT_EQ(g5.year(), 2014);
	EXPECT_EQ(g5.month(), 10);
	EXPECT_EQ(g5.day(), 1);
	g5.add_month(-1);
	EXPECT_EQ(g5.year(), 2014);
	EXPECT_EQ(g5.month(), 9);
	EXPECT_EQ(g5.day(), 1);
	g5.add_month(-1);
	EXPECT_EQ(g5.year(), 2014);
	EXPECT_EQ(g5.month(), 8);
	EXPECT_EQ(g5.day(), 1);
	g5.add_month(-1);
	EXPECT_EQ(g5.year(), 2014);
	EXPECT_EQ(g5.month(), 7);
	EXPECT_EQ(g5.day(), 1);

}

TEST(Gregorian, failing_kattis_tests) {
	Gregorian g1(1992,2,29);
	g1.add_month(29);
	EXPECT_EQ(g1.year(), 1994);
	EXPECT_EQ(g1.month(), 7);
	EXPECT_EQ(g1.day(), 28);

	Gregorian g2(1992,2,29);
	for (int i = 0; i < 29; ++i) {
		g2.add_month();
	}
	EXPECT_EQ(g2.year(), 1994);
	EXPECT_EQ(g2.month(), 7);
	EXPECT_EQ(g2.day(), 28);
}
