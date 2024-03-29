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

		bool set_date(int year, int month, int day);

		bool add_event(std::string);
		bool add_event(std::string, int);
		bool add_event(std::string, int, int);
		bool add_event(std::string, int, int, int);

		bool remove_event(std::string);
		bool remove_event(std::string, int);
		bool remove_event(std::string, int, int);
		bool remove_event(std::string, int, int, int);

		bool move_event(const Date & from, const Date & to);
		bool add_related_event(const Date & rel_date, int days, 
			std::string rel_event, std::string new_event);
		bool add_recurring_event();
		bool remove_recurring_event();
		bool print_events(const Date & start_date, const Date & end_date);
		int count_age();

		int get_future_events_index() const;
        int get_future_events_index(T const&) const;
		bool is_valid_date(int, int, int) const;
		int event_exists(std::string, int, int, int) const;

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

	//Moves an existing event to another date
	//Also moves all related events
	bool move_event(const Date & from, const Date & to){
		
		//Event not found
		return false;
	}

	//Adds a related event to an existing event by the amount of days they differ
	//When the parent even is removed or moved, the related event is too
 	bool add_related_event(const Date & rel_date, int days,
 		std::string rel_event, std::string new_event){
		
		//Event not found
		return false;
	}

	//Adds a recurring event
	//Can be set to partial dates or weekdays, default date is once per year
 	bool add_recurring_event(){
		return false;
	}

	//Removes recurring events
	//Can remove individual recurring events, such as the monthly meeting in December
 	bool remove_recurring_event(){
		return false;
	}

	//Prints all events from the start date to the end date
 	bool print_events(const Date & start_date, const Date & end_date){
		return false;
	}

	//Counts the age of someone?
 	int count_age(){
		return -1;
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


