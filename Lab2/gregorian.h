#ifndef GREGORIAN_H
#define GREGORIAN_H

#include "date.h"
#include "kattistime.cpp"
#include "jdn.c"

#include <string>
#include <iostream>

namespace lab2 {

	class Gregorian : public Date {
	private:
		int days_per_month [13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
		std::string week_day_names [8] = {"","monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
		std::string month_names [13] = {"", "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"};
		int days_per_week_ = 7;
		int months_per_year_ = 12;
		bool leap_year(int year) const;
		bool leap_year() const;

	public:
		virtual ~Gregorian(); // TODO
		Gregorian();
		Gregorian(const int a, const int b, const int c);

		virtual int week_day() const;
		virtual int days_per_week() const;
		virtual int months_per_year() const;
		virtual int days_this_month() const;
		virtual std::string week_day_name() const;
		virtual std::string month_name() const; // TODO

		virtual Date& operator+= (Date const&); // TODO
		virtual Date& operator-= (Date const&); // TODO
		virtual long mod_julian_day() const;

	};


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

	// http://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
	int Gregorian::week_day() const {
		/* Month table from wikipedia. month_table[0] is not to be used.
		   Index 1-12 is for january-december during non-leap years.
		   Index 13 is for january during leap year and index 14 for
		   February during leap years. */

		int d = this->day();
		int y = this->year() % 100; // Last two digits of year

		// Determine month number
		int adjust = 0; // Variable used to adjust for leap year in the month table
		if ( this->leap_year() ) { // Adjust for leap year
			if ( this->month() == 1 ) {
				adjust = 12;
			} else if ( this -> month() == 2) {
				adjust = 13;
			}
		}
		int month_table [15] = {-1,0,3,3,6,1,4,6,2,5,0,3,5,6,2};
		int m = month_table[ this->month() + adjust ];

		/* Determine century number 'c' according to Wikipedia article 
		mentioned above */
		int c;
		switch ( (this->month() / 100) % 4) { // First two digits of year mod 4
			case 0:
				c = 6;
				break;
			case 1:
				c = 4;
				break;
			case 2:
				c = 2;
				break;
			case 3:
				c = 0;
				break;
		}
		/* Return according to the formula from Wikipedia but with 
		adjustment to get monday == 1 and sunday == 7 */
		int res = (d + m + y + (y/4) + c) % 7;
		if (res == 0) {
			return 7;
		}
		return res; 
	}
	
	int Gregorian::days_per_week() const {
		return days_per_week_;
	}

	int Gregorian::months_per_year() const {
		return months_per_year_;
	}

	int Gregorian::days_this_month() const {
		if (this->month() != 2) {
			return days_per_month[this->month()];
		} else { // February --> check if leap year
			if ( leap_year( this->year() ) ) {
				return 1+days_per_month[this->month()];
			} else {
				return days_per_month[this->month()];
			}
		}
	}

	std::string Gregorian::week_day_name() const {
		return week_day_names[ this->week_day() ];
	}

	std::string Gregorian::month_name() const {
		return month_names[ this->month() ];
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

	Date& Gregorian::operator+= (Date const& rhs) {}
	Date& Gregorian::operator-= (Date const& rhs) {}

	long Gregorian::mod_julian_day() const {
		long jdn = ymd_to_jdn(this->year(), this->month(), this->day(), 0); // Last flag '0' is for Gregorian
		return jdn - MOD_JULIAN_DATE; // Need to adjust according to 17 nov 1858
	}

}

#endif // GREGORIAN_H
