#ifndef CALENDAR_H
#define CALENDAR_H

// #include "date.h"
#include "event.h"
#include <vector>
#include <iostream>

namespace lab2 {
	template <typename T> class Calendar {
	private:
	public:
		T current_date;
		std::vector<Event<T> > events;

        /**
         * Sets the current date of the calendar
         * @param  year  an int representing the year
         * @param  month an int representing the month
         * @param  day   an int representing the day
         * @return       True if the date is valid. Otherwise false.
         */
		bool set_date(int year, int month, int day);

        /**
         * Adds an event to the current date
         * @param  std::string The event description as a string
         * @return True if the event is successfully added. False if the
         *         date is not valid or the event already existed on that date.
         */
		bool add_event(std::string);

        /**
         * Adds an event to the current month and year on the day specified as parameters
         * @param  std::string The event description as a string
         * @param  day The day of the current year and month that the event is to be
         *         added to.
         * @return True if the event is successfully added. False if the
         *         date is not valid or the event already existed on that date.
         */
		bool add_event(std::string, int day);

        /**
         * Adds an event to the current year on the month and day specified as parameters
         * @param  std::string The event description as a string
         * @param  day The day of the current year that the event is to be
         *         added to.
         * @param  month The month of the current year that the event is to be
         *         added to.
         * @return True if the event is successfully added. False if the
         *         date is not valid or the event already existed on that date.
         */
		bool add_event(std::string, int day, int month);


        /**
         * Adds an event to the date specified in the parameters
         * @param  std::string The event description as a string
         * @param  day The day that the event is to be added to.
         * @param  month The month that the event is to be added to.
         * @param  year The year that the event is to be added to.
         * @return True if the event is successfully added. False if the
         *         date is not valid or the event already existed on that date.
         */
		bool add_event(std::string, int day, int month, int year);


        /**
         * Removes an event from the current date
         * @param  std::string The event description as a string
         * @return True if the event exists and is successfully removed. Otherwise false.
         */
		bool remove_event(std::string);

        /**
         * Removes an event from the current year on the month and day specified as parameters
         * @param  std::string The event description as a string
         * @param  day The day of the current year that the event is to be
         *         removed from.
         * @param  month The month of the current year that the event is to be
         *         removed from.
         * @return True if the event exists and is successfully removed. Otherwise false.
         */
		bool remove_event(std::string, int day);

        /**
         * Removes an event from the current year on the month and day specified as parameters
         * @param  std::string The event description as a string
         * @param  day The day of the current year that the event is to be
         *         removed from
         * @param  month The month of the current year that the event is to be
         *         removed from
         * @return True if the event exists and is successfully removed. Otherwise false.
         */
		bool remove_event(std::string, int day, int month);


        /**
         * Removes an event from the date specified in the parameters
         * @param  std::string The event description as a string
         * @param  day The day that the event is to be removed from.
         * @param  month The month that the event is to be removed from.
         * @param  year The year that the event is to be removed from.
         * @return True if the event exists and is successfully removed. Otherwise false.
         */
		bool remove_event(std::string, int day, int month, int year);

        /**
         * Returns the index of the first future event in the events vector
         * @return An int representing the index of the first future event.
         */
		int get_future_events_index() const;
        int get_future_events_index(T const&) const;

        /**
         * Checks if the provided date is a valid date in the current calendar
         * @param  year [description]
         * @param  month [description]
         * @param  day [description]
         * @return     True if the date is valid. Otherwise false.
         */
		bool is_valid_date(int year, int month, int day) const;

        /**
         * Checks if an event exists
         * @param  std::string  The event description
         * @param  year         The year of the searched event
         * @param  month        The month of the searched event
         * @param  day          The day of the searched event
         * @return              The index of the event in the events vector if the
         *                      event exists. -1 if the event do not exist.
         */
		int event_exists(std::string, int year, int month, int day) const;

		template <typename F>
		friend std::ostream& operator<< (std::ostream&, Calendar<F> const&);

		Calendar(); //Initializes with current date
		template <typename S>
		Calendar(Calendar<S> const&);
	};
}

#include "calendar.h"
#include <stdexcept>

namespace lab2 {

    //Sets the date of the calendar
    template <typename T>
    bool Calendar<T>::set_date(int year, int month, int day){
        
        //The date is not valid and can't be set
        if(!is_valid_date(year, month, day)){
            return false;
        }

        current_date = T(year, month, day);

        return true;
    }

    //Adds an event to the calendar given that the date is valid and the event doesn't already exist
    template <typename T>
    bool Calendar<T>::add_event(std::string event){
        return add_event(event, current_date.day(), current_date.month(), current_date.year());
    }

    template <typename T>
    bool Calendar<T>::add_event(std::string event, int day){
        return add_event(event, day, current_date.month(), current_date.year());
    }

    template <typename T>
    bool Calendar<T>::add_event(std::string event, int day, int month){
        return add_event(event, day, month, current_date.year());
    }

    template <typename T>
    bool Calendar<T>::add_event(std::string event, int day, int month, int year){
        
        //The date isn't valid, and can't be added
        if(!is_valid_date(year, month, day)){
            return false;
        }

        //The event already exists, and can't be added
        if(event_exists(event, year, month, day) != -1){
            return false;
        }

        T d = T(year, month, day);
        int index = get_future_events_index(d);
        Event<T> ev = Event<T>(event, d);

        //Adds the event to the appropriate index so the vector remains sorted
        events.insert(events.begin() + index, ev);

        return true;
    }

    //Removes an event from the calendar given that it exists
    template <typename T>
    bool Calendar<T>::remove_event(std::string event){
        return remove_event(event, current_date.day(), current_date.month(), current_date.year());
    }

    template <typename T>
    bool Calendar<T>::remove_event(std::string event, int day){
        return remove_event(event, day, current_date.month(), current_date.year());
    }

    template <typename T>
    bool Calendar<T>::remove_event(std::string event, int day, int month){
        return remove_event(event, day, month, current_date.year());
    }

    template <typename T>
    bool Calendar<T>::remove_event(std::string event, int day, int month, int year){
        int index = event_exists(event, year, month, day);

        //The event doesn't exist, and can't be removed
        if(index == -1){
            return false;
        }

        events.erase(events.begin() + index);

        return true;
    }

    //Check whether the date is valid
    template <typename T>
    bool Calendar<T>::is_valid_date(int year, int month, int day) const {

        try{
            T test = T(year, month, day);
        } catch (std::out_of_range & e){
            return false;
        }

        return true;
    }

    //Checks whether an event with the same name exists
    template <typename T>
    int Calendar<T>::event_exists(std::string event_name, int year, int month, int day) const {

        //Returns the index where the event exists
        for(int i = 0; i < events.size(); ++i){
            Event<T> event = events.at(i);
            if(event.get_name() == event_name && event.date.year() == year 
                && event.date.month() == month && event.date.day() == day){
                return i;
            }
        }

        return -1;
    }

    //Returns the index for all upcoming events from the current date
    template <typename T>
    int Calendar<T>::get_future_events_index() const {
        return get_future_events_index(this->current_date);
    }

    //Returns the index for all upcoming events from the current date
    template <typename T>
    int Calendar<T>::get_future_events_index(T const& d) const {

        for(int i = 0; i < events.size(); ++i){
            if(events.at(i).get_date() > d){
                return i;
            }
        }

        //If no upcoming events are found, all the events are in the past and we should add new to the end
        return events.size();
    }

    template <typename F>
    std::ostream& operator<< (std::ostream& output, Calendar<F> const& cal){
        for(int i = cal.get_future_events_index(); i < cal.events.size(); ++i){
            output << cal.events.at(i) << std::endl;
        }

        return output;
    }

    //Default constructor - Initializes the calendar with current date
    template <typename T>
    Calendar<T>::Calendar() {
        current_date = T();
    }

    //Copy constructor - Initializes the calendar with a given date
    template <typename T>
    template <typename S>
    Calendar<T>::Calendar(Calendar<S> const& rhs) {

        if ((size_t)this != (size_t)&rhs) {
            current_date = T(rhs.current_date);

            for (int i = 0; i < rhs.events.size(); ++i){
                Event<T> temp = Event<T>(rhs.events.at(i));
                events.push_back(temp);
            }
        }
    }
}

#endif // CALENDAR_H


