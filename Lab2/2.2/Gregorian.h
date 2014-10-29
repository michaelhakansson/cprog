#ifndef GREGORIAN_H
#define GREGORIAN_H

#include "../2.1/Date.h"
#include "../from_coursepage/kattistime.cpp"

#include <iostream>

namespace lab2 {

	class Gregorian : public Date {
	private:
		int days_per_week_ = 7;
		int months_per_year_ = 12;

	public:
		virtual ~Gregorian();
		Gregorian();
		Gregorian(const int a, const int b, const int c);

		virtual int days_per_week() const;
		virtual int months_per_year() const;

		virtual Date& operator++ ();
		virtual Date& operator-- ();
		virtual Date& operator+= (Date const&);
		virtual Date& operator-= (Date const&);
	};

	// TODO
	Gregorian::~Gregorian() {}

	Gregorian::Gregorian() : Date() {
		time_t tp;
		k_time(&tp);

	    struct tm *t = gmtime(&tp);
    	day_   = t->tm_mday;         // indexerade från ETT
    	month_ = t->tm_mon + 1;      // månaderna och dagarna
   		year_  = t->tm_year + 1900;
	}

	int Gregorian::days_per_week() const {
		return days_per_week_;
	}

	int Gregorian::months_per_year() const {
		return months_per_year_;
	}

	Date& Gregorian::operator++ () {}
	Date& Gregorian::operator-- () {}
	Date& Gregorian::operator+= (Date const& rhs) {}
	Date& Gregorian::operator-= (Date const& rhs) {}

	Gregorian::Gregorian(const int day, const int month, const int year)
		: Date(day, month, year) {}

}

#endif // GREGORIAN_H
