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
			virtual void inv_mod_julian_day(long jdn) = 0;

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
		long j = this->mod_julian_day();
		++j;
		this->inv_mod_julian_day(j);
		return *this;
	}

	Date& Date::operator-- () {
		long j = this->mod_julian_day();
		--j;
		this->inv_mod_julian_day(j);
		return *this;
	}

	Date& Date::operator-= (int n) {
		long j = this->mod_julian_day();
		j -= n;
		this->inv_mod_julian_day(j);
		return *this;
	}

	Date& Date::operator+= (int n) {
		long j = this->mod_julian_day();
		j += n;
		this->inv_mod_julian_day(j);
		return *this;
	}

	bool Date::operator== (Date const& rhs) const {
		long d1 = this->mod_julian_day();
		long d2 = rhs.mod_julian_day();
		return d1 == d2;
	}

	bool Date::operator!= (Date const& rhs) const {
		return !(this->operator==(rhs));
	}

	bool Date::operator< (Date const& rhs) const {
		long d1 = this->mod_julian_day();
		long d2 = rhs.mod_julian_day();
		return d1 < d2;
	}

	bool Date::operator<= (Date const& rhs) const {
		long d1 = this->mod_julian_day();
		long d2 = rhs.mod_julian_day();
		return d1 <= d2;
	}

	bool Date::operator> (Date const& rhs) const {
		long d1 = this->mod_julian_day();
		long d2 = rhs.mod_julian_day();
		return d1 > d2;
	}

	bool Date::operator>= (Date const& rhs) const {
		long d1 = this->mod_julian_day();
		long d2 = rhs.mod_julian_day();
		return d1 >= d2;
	}
	
	int Date::operator- (Date const& rhs) const {
		long d1 = this->mod_julian_day();
		long d2 = rhs.mod_julian_day();
		return d1 - d2;
	}
}

#endif // DATE_H
