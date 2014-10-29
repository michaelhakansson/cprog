#ifndef DATE_H
#define DATE_H

#include <ostream>

namespace lab2 {
	class Date {
		protected:
			int day_;
			int month_;
			int year_;

		public:
			// Default constructor - should initiate to todays date
			Date();
			
			// Constructor taking a date
			Date(const int day, const int month, const int year);

			// Copy constructor
			Date(Date const&);

			// Destructor
			virtual ~Date();

			// Copy assignment
			Date& operator= (Date const&);

			int year() const;
			int day() const;
			int month() const;
			int week_day() const; // TODO
			virtual int days_per_week() const = 0;
			virtual int months_per_year() const = 0;
			virtual int days_this_month() const = 0;
			virtual std::string week_day_name() const = 0;
			virtual std::string month_name() const = 0;

			// Returntype void since only setter
			void add_year(const int);
			void add_month(const int);

			// Operator overloads
			virtual Date& operator++ () =  0;
			virtual Date& operator-- () = 0;
			virtual Date& operator+= (Date const&) = 0;
			virtual Date& operator-= (Date const&) = 0;
			bool  operator== (Date const&) const; // TODO
			bool  operator!= (Date const&) const; // TODO
			bool  operator<  (Date const&) const; // TODO
			bool  operator<= (Date const&) const; // TODO
			bool  operator>  (Date const&) const; // TODO
			bool  operator>= (Date const&) const; // TODO
			int   operator-  (Date const&) const; // TODO
			friend std::ostream& operator<< (std::ostream&, Date const&);

			virtual int mod_julian_day(Date const&) const;
	};

	// TODO
	Date::~Date() {}

	Date::Date() {}

	Date::Date(const int day, const int month, const int year)
		: day_(day), month_(month), year_(year) {}

	int Date::month() const {
		return month_;
	}

	int Date::day() const {
		return day_;
	}

	int Date::year() const {
		return year_;
	}

	// TODO
	int Date::mod_julian_day(Date const&) const {
		return 1;
	}

	std::ostream& operator<< (std::ostream& output, Date const& date) {
		output << date.year() << "-" <<
				 (date.month() < 10 ? "0" : "") << date.month() << "-" << 
				 (date.day() < 10 ? "0" : "") << date.day();
		return output;
	}
}

#endif // DATE_H
