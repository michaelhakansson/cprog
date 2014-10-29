#ifndef DATE_H
#define DATE_H

#include <ostream>

namespace lab2 {

	class Date {
		private:
			int year_;
			int month_;
			int day_;
			int days_per_week_;

		public:
			// Default constructor - should initiate to todays date
			Date();
			
			// Constructor taking a date
			Date(const int day, const int month, const int year);

			// Copy constructor
			Date(Date const&);

			// Destructor
			~Date();

			// Copy assignment
			Date& operator= (Date const&);

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
			virtual Date& operator+= (Date const&) = 0;
			virtual Date& operator-= (Date const&) = 0;
			bool  operator== (Date const&) const;
			bool  operator!= (Date const&) const;
			bool  operator<  (Date const&) const;
			bool  operator<= (Date const&) const;
			bool  operator>  (Date const&) const;
			bool  operator>= (Date const&) const;
			int   operator-  (Date const&) const;
			friend std::ostream& operator<< (std::ostream&, Date const&);

			virtual int mod_julian_day(Date const&) const;

	};

}

#endif // DATE_H
