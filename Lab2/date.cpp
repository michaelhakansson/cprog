#include "date.h"

namespace lab2 {
    Date::Date() {}

	Date::Date(const int, const int, const int) {}

	Date::Date(Date const& rhs) {
		jdn_ = rhs.mod_julian_day();
	}

	std::ostream& operator<< (std::ostream& output, Date const& date) {
		output << date.year() << "-" <<
				 (date.month() < 10 ? "0" : "") << date.month() << "-" << 
				 (date.day() < 10 ? "0" : "") << date.day();
		return output;
	}

	Date& Date::operator= (Date const& rhs) {
		if (this != &rhs) {
			jdn_ = rhs.mod_julian_day();
		}
		return *this;
	}

	Date& Date::operator++ () {
		++jdn_;
		return *this;
	}

	Date& Date::operator-- () {
		--jdn_;
		return *this;
	}

	Date& Date::operator-= (int n) {
		jdn_ -= n;
		return *this;
	}

	Date& Date::operator+= (int n) {
		jdn_ += n;
		return *this;
	}

	bool Date::operator== (Date const& rhs) const {
		return jdn_ == rhs.mod_julian_day();
	}

	bool Date::operator!= (Date const& rhs) const {
		return jdn_ != rhs.mod_julian_day();
	}

	bool Date::operator< (Date const& rhs) const {
		return jdn_ < rhs.mod_julian_day();
	}

	bool Date::operator<= (Date const& rhs) const {
		return jdn_ <= rhs.mod_julian_day();
	}

	bool Date::operator> (Date const& rhs) const {
		return jdn_ > rhs.mod_julian_day();
	}

	bool Date::operator>= (Date const& rhs) const {
		return jdn_ >= rhs.mod_julian_day();
	}

	int Date::operator- (Date const& rhs) const {
		return jdn_ - rhs.mod_julian_day();
	}
	
}