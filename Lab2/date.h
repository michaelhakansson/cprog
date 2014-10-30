#ifndef DATE_H
#define DATE_H

#include <ostream>

namespace lab2 {
	class Date {
		protected:
			int day_;
			int month_;
			int year_;
			static const long MOD_JULIAN_DATE = 2400001;

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
			virtual int week_day() const = 0;
			virtual int days_per_week() const = 0;
			virtual int months_per_year() const = 0;
			virtual int days_this_month() const = 0;
			virtual std::string week_day_name() const = 0;
			virtual std::string month_name() const = 0;

			// Returntype void since only setter
			void add_year(const int);
			void add_month(const int);

			// Operator overloads
			Date& operator++ ();
			Date& operator-- ();
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

			virtual long mod_julian_day() const = 0;
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

	std::ostream& operator<< (std::ostream& output, Date const& date) {
		output << date.year() << "-" <<
				 (date.month() < 10 ? "0" : "") << date.month() << "-" << 
				 (date.day() < 10 ? "0" : "") << date.day();
		return output;
	}

	Date& Date::operator++ () {
		if ( this->days_this_month() > this->day() ) { // OK to add day this month
			++day_;
		} else {
			if ( this->months_per_year() > this->month() ) { // OK to add month this year
				++month_; // Increment month
				day_ = 1; // Set day to first of the year
			} else { // Must add a year
				++year_;
				month_ = 1;
				day_  = 1;
			}
		}
		return *this;
	}

	Date& Date::operator-- () {
		if ( this->day() > 1 ) { // OK to decrement day
			--day_;
		} else {
			if ( this->month() > 1 ) { // OK to decrement month
				--month_; // Increment month
				// Set day to the last day of the month
				day_ = this->days_this_month();
			} else { // Must decrement the year
				--year_;
				month_ = this->months_per_year();
				day_  = this->days_this_month();
			}
		}
		return *this;
	}
}

#endif // DATE_H
