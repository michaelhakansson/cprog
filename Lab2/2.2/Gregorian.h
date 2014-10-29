#ifndef GREGORIAN_H
#define GREGORIAN_H

#include "../2.1/Date.h"

#include <iostream>

namespace lab2 {

	class Gregorian : public Date {
	private:
		int days_per_week_;
		int months_per_year_;

	public:
		virtual ~Gregorian();
		Gregorian(const int a, const int b, const int c);

		virtual int days_per_week() const;
		virtual int months_per_year() const;

		virtual Date& operator++ ();
		virtual Date& operator-- ();
		virtual Date& operator+= (Date const&);
		virtual Date& operator-= (Date const&);
	};

	// TODO
	Gregorian::~Gregorian() {}

	int Gregorian::days_per_week() const {
		return days_per_week_;
	}

	int Gregorian::months_per_year() const {
		return months_per_year_;
	}

	Date& Gregorian::operator++ () {}
	Date& Gregorian::operator-- () {}
	Date& Gregorian::operator+= (Date const& rhs) {}
	Date& Gregorian::operator-= (Date const& rhs) {}

	Gregorian::Gregorian(const int day, const int month, const int year) : 
		Date(day, month, year), days_per_week_(7), months_per_year_(12) {}

}

#endif // GREGORIAN_H
