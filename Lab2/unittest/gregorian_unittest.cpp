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
	
	EXPECT_EQ(g1.mod_julian_day(), -1);
	EXPECT_EQ(g2.mod_julian_day(),  0);
	EXPECT_EQ(g3.mod_julian_day(),  1);

}

TEST(Gregorian, week_day_number) {
	Gregorian g1(30,10,2014);
	Gregorian g2(31,10,2014);
	Gregorian g3(31,10,2006);
	EXPECT_EQ(g1.week_day(), 4);
	EXPECT_EQ(g2.week_day(), 5);
	EXPECT_EQ(g3.week_day(), 2);
}
