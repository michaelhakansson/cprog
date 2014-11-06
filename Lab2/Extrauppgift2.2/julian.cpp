#include "julian.h"
#include "kattistime.h"

#include <iostream>
#include <stdexcept>

namespace lab2 {

    const int days_per_month [13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	const std::string week_day_names [8] = {"","monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
	const std::string month_names [13] = {"", "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"};
	const int days_per_week_ = 7;
	const int months_per_year_ = 12;

	Julian::Julian() : Date() {
		time_t tp;
		k_time(&tp);

		struct tm *t = gmtime(&tp);

		// Expect Gregorian input
		long jdn = ymd_to_jdn(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, 0);
		
		int year;
		int month;
		int day;
		jdn_to_ymd(jdn, &year, &month, &day, 1);


		if ( !valid_date(year, month, day) ) {
			throw std::out_of_range("Invalid date"); 
		}

		jdn_ = jdn;
	}

	Julian::Julian(const int year, const int month, const int day) {
		if ( !valid_date(year, month, day) ) {
			throw std::out_of_range("Invalid date"); 
		}
		jdn_ = ymd_to_jdn(year, month, day);
	}

	Julian::Julian(Date const& rhs) {
		jdn_ = rhs.mod_julian_day();
	}


	int Julian::year() const {
		int year, month, day;
		jdn_to_ymd(jdn_, &year, &month, &day);
		return year;
	}

	int Julian::month() const {
		int year, month, day;
		jdn_to_ymd(jdn_, &year, &month, &day);
		return month;
	}

	int Julian::day() const {
		int year, month, day;
		jdn_to_ymd(jdn_, &year, &month, &day);
		return day;
	}

	int Julian::week_day() const {
	// http://en.wikipedia.org/wiki/Julian_day#Finding_day_of_week_given_Julian_day_number
	// Must have the complete julian day
		long jdn = this->mod_julian_day() + MOD_JULIAN_DATE;
		if (jdn < 0) {
			return ((-jdn) % 7) + 1;
		}
		return (jdn % 7) + 1;
	}
	
	int Julian::days_per_week() const {
		return days_per_week_;
	}

	int Julian::months_per_year() const {
		return months_per_year_;
	}

	int Julian::days_this_month() const {
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

	std::string Julian::week_day_name() const {
        if (week_day() < 0 || week_day() > 7) {
            throw std::out_of_range("Invalid week_day number");
        }
		return week_day_names[ week_day() ];
	}

	std::string Julian::month_name() const {
		int month_nr = this->month();
        if (month_nr < 0 || month_nr > 12) {
            throw std::out_of_range("Invalid month number");
        }
		return month_names[month_nr] ;
	}

	// Calculate leap year http://support.microsoft.com/kb/214019
	bool Julian::leap_year(int year) const {
		if (year % 4 == 0) {return true;}
		return false;
	}

	bool Julian::leap_year() const {
		return leap_year(year());
	}

	bool Julian::valid_date(int year, int month, int day) const {
		if (year < 1) return false;
		if (month < 1 || month > this->months_per_year()) return false;
		return ( day > 0 && day <= (days_per_month[month] + ((leap_year(year) && month == 2) ? 1 : 0)) );
	}

	long Julian::mod_julian_day() const {
		return jdn_;
	}

	void Julian::add_year(const int i) {
		// Going from leap year to non leap year. If february 29, change the day to 28.
		int y = year();
		int m = month();
		int d = day();
		if ( this->leap_year() && !leap_year( y+i ) && m == 2 && d == 29 ) {
			d = 28;
		}
		y += i;
		jdn_ = ymd_to_jdn(y, m, d);
	}

	void Julian::add_month(const int i) {
		// Do as many times as input says.
		for (int j = 0, k = i < 0 ? -i : i; j < k; ++j) {
			int change_to_month = month();
			int change_to_year = year();
			if (i > 0) {
				if (month() == 12) {
					change_to_month = 1;
					++change_to_year;	
				} else {
					++change_to_month;
				}
			} else { // Decrease month
				if (month() == 1) {
					change_to_month = 12;
					--change_to_year;
				} else {
					--change_to_month;
				}
			}
			if ( valid_date( change_to_year, change_to_month, day() ) ) {
				jdn_ = ymd_to_jdn(change_to_year, change_to_month, day());
			} else {
				jdn_ = mod_julian_day() + (i < 0 ? -30 : 30); // Get julian day number
			}
		}
	}

	#ifdef PAPAL                    /* Pope Gregory XIII's decree */
	#define LASTJULDATE 15821004L   /* last day to use Julian calendar */
	#define LASTJULJDN  2299160L    /* jdn of same */
	#else                           /* British-American usage */
	#define LASTJULDATE 17520902L   /* last day to use Julian calendar */
	#define LASTJULJDN  2361221L    /* jdn of same */
	#endif


	long Julian::ymd_to_jdn(int y, int m, int d, int julian) const {
	    long jdn;

	    if (julian < 0)         /* set Julian flag if auto set */
	            julian = (((y * 100L) + m) * 100 + d  <=  LASTJULDATE);

	    if (y < 0)              /* adjust BC year */
	            y++;

	    if (julian)
	            jdn = 367L * y - 7 * (y + 5001L + (m - 9) / 7) / 4
	            + 275 * m / 9 + d + 1729777L;
	    else
	            jdn = (long)(d - 32076)
	            + 1461L * (y + 4800L + (m - 14) / 12) / 4
	            + 367 * (m - 2 - (m - 14) / 12 * 12) / 12
	            - 3 * ((y + 4900L + (m - 14) / 12) / 100) / 4
	            + 1;            /* correction by rdg */

	    return jdn - MOD_JULIAN_DATE;
	}


	void Julian::jdn_to_ymd(long jdn, int *yy, int *mm, int *dd, int julian) const {
		jdn += MOD_JULIAN_DATE;
	    long x, z, m, d, y;
	    long daysPer400Years = 146097L;
	    long fudgedDaysPer4000Years = 1460970L + 31;

	    if (julian < 0)                 /* set Julian flag if auto set */
	            julian = (jdn <= LASTJULJDN);

	    x = jdn + 68569L;
	    if ( julian )
	    {
	            x += 38;
	            daysPer400Years = 146100L;
	            fudgedDaysPer4000Years = 1461000L + 1;
	    }
	    z = 4 * x / daysPer400Years;
	    x = x - (daysPer400Years * z + 3) / 4;
	    y = 4000 * (x + 1) / fudgedDaysPer4000Years;
	    x = x - 1461 * y / 4 + 31;
	    m = 80 * x / 2447;
	    d = x - 2447 * m / 80;
	    x = m / 11;
	    m = m + 2 - 12 * x;
	    y = 100 * (z - 49) + y + x;

	    *yy = (int)y;
	    *mm = (int)m;
	    *dd = (int)d;

	    if (*yy <= 0)                   /* adjust BC years */
	            (*yy)--;
	}

}
