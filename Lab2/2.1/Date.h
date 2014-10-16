#ifndef DATE_H
#define DATE_H

#include <ostream>

namespace lab2 {

	class Date {
		private:
			int year;
			int month;
			int day;
			int days_per_week();

		public:
			// Default constructor - should initiate to todays date
			Date();
			
			// Constructor taking a date
			Date(const int day, const int month, const int year);

			// Copy constructor
			Date(const Date&);

			// Destructor
			~Date();

			// Copy assignment
			Date& operator= (const Date&);

			int year() const;
			int day() const;
			int month() const;
			int week_day() const;
			int days_per_week() const;
			int months_per_year() const;
			std::string week_day_name() const;
			std::string month_name() const;

			// Returntype void since only setter
			void add_year(const int);
			void add_month(const int);

			// Operator overloads
			virtual Date& operator++ () = 0; // Should increase day
			virtual Date& operator-- () = 0; // Should decrease day
			virtual Date& operator+= () = 0;
			virtual Date& operator-= () = 0;
			bool  operator== (const Date&) const;
			bool  operator!= (const Date&) const;
			bool  operator<  (const Date&) const;
			bool  operator<= (const Date&) const;
			bool  operator>  (const Date&) const;
			bool  operator>= (const Date&) const;
			int   operator-  (const Date&) const;

			virtual int mod_julian_day(const &Date) const;

			ostream &operator<< (ostream&, const Date&) const;

	};

}

#endif // DATE_H
