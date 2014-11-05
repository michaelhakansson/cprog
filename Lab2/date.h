#ifndef DATE_H
#define DATE_H

#include <string>
#include <ostream>

namespace lab2 {
    class Date {
		protected:
			long jdn_;
			static const long MOD_JULIAN_DATE = 2400001;

		public:
			// Constructors
			Date(); // Initiates to current date
			Date(const int year, const int month, const int day);
			Date(Date const&);

			virtual int year() const = 0;
			virtual int day() const = 0;
			virtual int month() const = 0;
			virtual int week_day() const = 0;
			virtual int days_per_week() const = 0;
			virtual int months_per_year() const = 0;
			virtual int days_this_month() const = 0;
			virtual std::string week_day_name() const = 0;
			virtual std::string month_name() const = 0;
			virtual long mod_julian_day() const = 0;
			virtual void add_year(const int i = 1) = 0;
			virtual void add_month(const int i = 1) = 0;

			// Operator overloads
			Date& operator= (Date const& rhs);
			Date& operator++ ();
			Date& operator-- ();
			Date& operator-= (int);
			Date& operator+= (int);
			bool  operator== (Date const&) const;
			bool  operator!= (Date const&) const;
			bool  operator<  (Date const&) const;
			bool  operator<= (Date const&) const;
			bool  operator>  (Date const&) const;
			bool  operator>= (Date const&) const;
			int   operator-  (Date const&) const;
			friend std::ostream& operator<< (std::ostream&, Date const&);
	};
}

#endif // DATE_H
