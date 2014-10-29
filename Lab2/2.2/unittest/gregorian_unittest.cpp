#include "../../gtest-1.7.0/include/gtest/gtest.h"
#include "../Gregorian.h"
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
	Gregorian g(13,03,2001);
	EXPECT_EQ(g.day(), 13);
	EXPECT_EQ(g.month(), 03);
	EXPECT_EQ(g.year(), 2001);
}

TEST(Gregorian, output_test) {
	Gregorian g1(01,01,2000);
	Gregorian g2(22,11,1921);
	
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
}
