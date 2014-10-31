#ifndef GREGORIAN_H
#define GREGORIAN_H

#include "date.h"

namespace lab2 {

	class Gregorian : public Date {
	private:
		bool leap_year(int year) const;
		bool leap_year() const;
		void inv_mod_julian_day(long jdn);
		bool valid_date(const int day, const int month, const int year) const;

	public:
		Gregorian();
		Gregorian(const int day, const int month, const int year);

		virtual int week_day() const;
		virtual int days_per_week() const;
		virtual int months_per_year() const;
		virtual int days_this_month() const;
		virtual std::string week_day_name() const;
		virtual std::string month_name() const;
		virtual long mod_julian_day() const;
		virtual void add_year(const int);
		virtual void add_month(const int);

	};
}
#endif // GREGORIAN_H


// THIS WILL GO INTO "gregorian.cpp"
// #include "gregorian.h" // TODO: Uncomment this line
#include "kattistime.cpp"
#include "jdn.c"

#include <string>
#include <iostream>
#include <stdexcept>

namespace lab2 {

	const int days_per_month [13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	const std::string week_day_names [8] = {"","monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
	const std::string month_names [13] = {"", "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"};
	const int days_per_week_ = 7;
	const int months_per_year_ = 12;
	
	Gregorian::Gregorian() : Date() {
		time_t tp;
		k_time(&tp);

	    struct tm *t = gmtime(&tp);
    	day_   = t->tm_mday;         // indexerade från ETT
    	month_ = t->tm_mon + 1;      // månaderna och dagarna
   		year_  = t->tm_year + 1900;
	}

	Gregorian::Gregorian(const int day, const int month, const int year) {
		if ( !valid_date(day, month, year) ) {
			throw std::out_of_range("Invalid date"); 
		}
		day_ = day;
		month_ = month;
		year_ = year;
	}

	// http://en.wikipedia.org/wiki/Julian_day#Finding_day_of_week_given_Julian_day_number
	/* Returns the day of the week. Monday = 1, sunday = 7.*/
	int Gregorian::week_day() const {
		// Must have the complete julian day
		long jdn = this->mod_julian_day() + MOD_JULIAN_DATE;
		if (jdn < 0) {
			return ((-jdn) % 7) + 1;
		}
		return (jdn % 7) + 1;
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

	bool Gregorian::valid_date(int day, int month, int year) const {
		if (year < 1) return false;
		if (month < 1 || month > this->months_per_year()) return false;
		return ( day <= days_per_month[ month + (leap_year(year) ? 1 : 0) ] );
	}

	long Gregorian::mod_julian_day() const {
		long jdn = ymd_to_jdn(this->year(), this->month(), this->day(), 0); // Last flag '0' is for Gregorian
		return jdn - MOD_JULIAN_DATE; // Need to adjust according to 17 nov 1858
	}

	void Gregorian::inv_mod_julian_day(long jdn) {
		jdn_to_ymd(jdn + MOD_JULIAN_DATE, &year_, &month_, &day_, 0); // 0 as last argument for Gregorian
	}

	void Gregorian::add_year(const int i = 1) {
		// Going from leap year to non leap year. If february 29, change the day to 28.
		if ( this->leap_year() && !leap_year( year()+i ) && month() == 2 && day() == 29 ) {
			day_ = 28;
		}
		year_ += i;
	}

	void Gregorian::add_month(const int i = 1) {}

}


