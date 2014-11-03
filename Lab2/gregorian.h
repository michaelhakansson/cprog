#ifndef GREGORIAN_H
#define GREGORIAN_H

#include "date.h"

#include <string>

namespace lab2 {

    class Gregorian : public Date {
	protected:
		virtual bool leap_year(int year) const;
		virtual bool leap_year() const;
		virtual bool valid_date(const int year, const int month, const int day) const;
		virtual long ymd_to_jdn(int y, int m, int d) const;
		virtual void jdn_to_ymd(long jdn, int *yy, int *mm, int *dd) const;
	
	public:
		Gregorian();
		Gregorian(const int year, const int month, const int day);
		Gregorian(Date const& rhs);

		virtual int year() const;
		virtual int month() const;
		virtual int day() const;
		virtual int week_day() const;
		virtual int days_per_week() const;
		virtual int months_per_year() const;
		virtual int days_this_month() const;
		virtual std::string week_day_name() const;
		virtual std::string month_name() const;
		virtual long mod_julian_day() const;
		virtual void add_year(const int i = 1);
		virtual void add_month(const int i = 1);
	};
}
#endif // GREGORIAN_H
