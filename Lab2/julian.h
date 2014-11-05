#ifndef JULIAN_H
#define JULIAN_H

#include "date.h"

#include <string>

namespace lab2 {

    class Julian : public Date {
	protected:
		/**
		 * Calculates if a year is a leap year or not according to the 
		 * julian calendar.
		 * @param  An int representing the year
		 * @return A bool 'true' if the year is a leap year, and 'false'
		 * otherwise.
		 */
		virtual bool leap_year(int year) const;

		/**
		 * Calculates if the current year is a leap year or not according
		 * to the julian calendar.
		 * @return A bool 'true' if the year is a leap year, and 'false'
		 * otherwise.
		 */
		virtual bool leap_year() const;

		/**
		 * Calculates if the provided date is a valid date according
		 * to the julian calendar.
		 * @param  year An int representing the year
		 * @param  month An int representing the month
		 * @param  day An int representing the day
		 * @return A bool 'true' if the date is valid, and 'false' otherwise.
		 */
		virtual bool valid_date(const int year, const int month, const int day) const;
		
		/**
		 * Calculates the julian day number of a julian date.
		 * @param  y An int representing the year
		 * @param  m An int representing the month
		 * @param  d An int representing the day
		 * @return A long representing the julian day number of the
		 * provided date.
		 */
		virtual long ymd_to_jdn(int y, int m, int d, int julian = 1) const;
		
		/**
		 * Calculates the year, month and day in a julian calendar
		 * given a julian day number.
		 * @param jdn A long representing the julian day number
		 * @param yy A pointer to an int that will be set to the year in a julian calendar
		 * @param mm A pointer to an int that will be set to the month in a julian calendar
		 * @param dd A pointer to an int that will be set to the day in a julian calendar
		 */
		virtual void jdn_to_ymd(long jdn, int *yy, int *mm, int *dd, int julian = 1) const;
	
	public:
		/**
	 	* Default constructor for a julian date. Uses todays date.
	 	*/
		Julian();

		/**
		 * Constructs a date with specified date.
		 * @param year The wanted year
		 * @param month The wanted month
		 * @param day The wanted year
		 */
		Julian(const int year, const int month, const int day);

		/**
		 * Copy construct a julian date from another Date object.
		 * @param rhs A reference to the copied from Date object.
		 */	
		Julian(Date const& rhs);

		/**
		 * Getter for the year
		 * @return An int representing the year in a julian calendar
		 */
		virtual int year() const;

		/**
		 * Getter for the month
		 * @return An int representing the month in a julian calendar
		 */		
		virtual int month() const;

		/**
		 * Getter for the day
		 * @return An int representing the day in a julian calendar
		 */
		virtual int day() const;

		/**
		 * Calculates the week day number of the date
		 * @return An int representing the day number where monday == 1 and
		 * sunday == 7.
		 */
		virtual int week_day() const;

		/**
		 * Getter for days per week in a julian calendar.
		 * @return An int representing the number of days per week.
		 * As long as no one makes radical changes to the julian
		 * calendar, this will always be 7.
		 */
		virtual int days_per_week() const;

		/**
		 * Getter for months per year in a julian calendar.
		 * @return An int representing the number of months per year.
		 * As long as no one makes radical changes to the julian
		 * calendar, this will always be 12.
		 */
		virtual int months_per_year() const;

		/**
		 * Calculates the number of days this month.
		 * @return An int representing the days of the current month.
		 * This function takes into account leap years.
		 */
		virtual int days_this_month() const;

		/**
		 * Returns the name of the current week day.
		 * @return A std::string representing the day name in english.
		 */
		virtual std::string week_day_name() const;

		/**
		 * Returns the name of the current month.
		 * @return A std::string representing the month name in english.
		 */		
		virtual std::string month_name() const;

		/**
		 * Accesses the number of days since the last modified
		 * julian day this date represents.
		 * @return A long representing the number of days since
		 * the last modified julian day.
		 */
		virtual long mod_julian_day() const;

		/**
		 * Adds a year to the current date. If current year is a leap year and
		 * the resulting date is not a leap year, the new date will be feb 28:th.
		 * If the new year is also a leap year though, the new date will also
		 * be feb 29:th.
		 * @param i An int. If no parameter is passed along, one (1) year 
		 * will be added. A negative parameters can be used.
		 */
		virtual void add_year(const int i = 1);

		/**
		 * Adds a month to the current date. If the new date is not valid, for
		 * example going from january 31 to february 31, 30 days is instead added.
		 * @param i An int. If no parameter is passed along, one (1) month 
		 * will be added. A negative parameters can be used. Passing parameter
		 * X is the same as performing add_month() X times.
		 */
		virtual void add_month(const int i = 1);
	};
}
#endif // JULIAN_H