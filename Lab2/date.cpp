#include "date.h"

namespace lab2 {
    Date::Date() {}

	Date::Date(const int, const int, const int) {}

	Date::Date(Date const& rhs) {
		jdn_ = rhs.mod_julian_day();
	}

	/* Output operator. The date is printed as 'yyyy-mm-dd' */
	std::ostream& operator<< (std::ostream& output, Date const& date) {
		output << date.year() << "-" <<
				 (date.month() < 10 ? "0" : "") << date.month() << "-" << 
				 (date.day() < 10 ? "0" : "") << date.day();
		return output;
	}

	/* Increments the date by one day. */
	Date& Date::operator++ () {
		++jdn_;
		return *this;
	}

	
	/* Decrements the date by one day. */
	Date& Date::operator-- () {
		--jdn_;
		return *this;
	}

	/* Increments the date by 'n' days. */
	Date& Date::operator+= (int n) {
		jdn_ += n;
		return *this;
	}

	/* Decrements the date by 'n' days. */
	Date& Date::operator-= (int n) {
		jdn_ -= n;
		return *this;
	}

	/* Compares two Date objects and return a bool. */
	bool Date::operator== (Date const& rhs) const {
		return jdn_ == rhs.mod_julian_day();
	}

	/* Compares two Date objects and return a bool. */
	bool Date::operator!= (Date const& rhs) const {
		return jdn_ != rhs.mod_julian_day();
	}

	/* Compares two Date objects and return a bool. */
	bool Date::operator< (Date const& rhs) const {
		return jdn_ < rhs.mod_julian_day();
	}

	/* Compares two Date objects and return a bool. */
	bool Date::operator<= (Date const& rhs) const {
		return jdn_ <= rhs.mod_julian_day();
	}

	/* Compares two Date objects and return a bool. */
	bool Date::operator> (Date const& rhs) const {
		return jdn_ > rhs.mod_julian_day();
	}

	/* Compares two Date objects and return a bool. */
	bool Date::operator>= (Date const& rhs) const {
		return jdn_ >= rhs.mod_julian_day();
	}

	/* Compares two Date objects and return a bool. */
	int Date::operator- (Date const& rhs) const {
		return jdn_ - rhs.mod_julian_day();
	}
	
}