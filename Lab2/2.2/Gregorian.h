#ifndef GREGORIAN_H
#define GREGORIAN_H

#include "../2.1/Date.h"
#include "../from_coursepage/kattistime.cpp"

#include <iostream>

namespace lab2 {

	class Gregorian : public Date {
	private:
		int days_per_month [13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
		int days_per_week_ = 7;
		int months_per_year_ = 12;

	public:
		virtual ~Gregorian();
		Gregorian();
		Gregorian(const int a, const int b, const int c);

		virtual int days_per_week() const;
		virtual int months_per_year() const;
		virtual int days_this_month() const;

		virtual Date& operator++ ();
		virtual Date& operator-- ();
		virtual Date& operator+= (Date const&);
		virtual Date& operator-= (Date const&);

		bool leap_year(int year) const;
		bool leap_year() const;
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

	Gregorian::Gregorian(const int day, const int month, const int year)
		: Date(day, month, year) {}

	int Gregorian::days_per_week() const {
		return days_per_week_;
	}

	int Gregorian::months_per_year() const {
		return months_per_year_;
	}

	// TODO
	int Gregorian::days_this_month() const {
		if (this->month() != 2) {
			return days_per_month[this->month()];
		} else { // February --> check leap year
			if ( leap_year( this->year() ) ) {
				return 1+days_per_month[this->month()];
			} else {
				return days_per_month[this->month()];
			}
		}
	}

	// Calculate leap year http://support.microsoft.com/kb/214019
	bool Gregorian::leap_year(int year) const {
		if (year % 400 == 0) {return true;}
		if (year % 100 == 0) {return false;}
		if (year % 4 == 0) {return true;}
		return false;
	}

	bool Gregorian::leap_year() const {
		return leap_year(year_);
	}

	Date& Gregorian::operator++ () {}
	Date& Gregorian::operator-- () {}
	Date& Gregorian::operator+= (Date const& rhs) {}
	Date& Gregorian::operator-= (Date const& rhs) {}


}

#endif // GREGORIAN_H
