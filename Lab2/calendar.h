#ifndef CALENDAR_H
#define CALENDAR_H

#include "date.h"
#include "event.h"
#include <stdexcept>

namespace lab2 {
	template <typename T>
	class Calendar<T> {
	private:
		T & current_date;
		std::vector<Event> events;
	public:
		Calendar(); //Initializes with current date
		Calendar(Date const&)

		bool set_date(int, int, int);

		bool add_event(std::string);
		bool add_event(std::string, int);
		bool add_event(std::string, int, int);
		bool add_event(std::string, int, int, int);

		bool remove_event(std::string);
		bool remove_event(std::string, int);
		bool remove_event(std::string, int, int);
		bool remove_event(std::string, int, int, int);

		bool is_valid_date(int, int, int);
		int event_exists(std::string, int, int, int);
		friend std::ostream& operator<< (std::ostream&, Calendar<T> const&);
	};
}

#endif // CALENDAR_H

//Sets the date of the calendar
bool set_date(int year, int month, int day){
	
	//The date is not valid and can't be set
	if(!is_valid_date(year, month, day)){
		return false;
	}

	current_date = new Date(year, month, day);

	return true;
}

//Adds an event to the calendar given that the date is valid and the event doesn't already exist
template <typename T>
bool Calendar<T>::add_event(std::string event){
	return add_event(event, current_date.year(), current_date.month(), current_date.day());
}

template <typename T>
bool Calendar<T>::add_event(std::string event, int day){
	return add_event(event, current_date.year(), current_date.month(), day);
}

template <typename T>
bool Calendar<T>::add_event(std::string event, int month, int day){
	return add_event(event, current_date.year(), month, day);
}

template <typename T>
bool Calendar<T>::add_event(std::string event, int year, int month, int day){
	
	//The date isn't valid, and can't be added
	if(!is_valid_date(year, month, day)){
		return false;
	}

	//The event already exists, and can't be added
	if(event_exists(event, year, month, day) != -1){
		return false;
	}

	T d = new T(year, month, day)
	int index = get_future_events_index(d);

	//Adds the event to the appropriate index so the vector remains sorted
	events.insert(index, new Event(event, d));

	return true;
}

//Removes an event from the calendar given that it exists
bool remove_event(std::string event){
	return remove_event(event, current_date.year(), current_date.month(), current_date.day());
}

bool remove_event(std::string event, int day){
	return remove_event(event, current_date.year(), current_date.month(), day);
}

bool remove_event(std::string event, int month, int day){
	return remove_event(event, current_date.year(), month, day);
}

bool remove_event(std::string event, int year, int month, int day){
	return remove_event(event, year, month, day);
}

bool remove_event(std::string event, int year, int month, int day){
	
	int index = event_exists(event, year, month, day);

	//The event doesn't exist, and can't be removed
	if(index == -1){
		return false;
	}

	events.erase(index);

	return true;
}

//Check whether the date is valid
bool is_valid_date(int year, int month, int day){

	try{
		T test = T(year, month, day);
	} catch (std::out_of_range & e){
		return false;
	}

	return true
}

//Checks whether an event with the same name exists
int event_exists(std::string event_name, int year, int month, int day){

	//Returns the index where the event exists
	for(int i = 0; i < this.events.size(); ++i){
		if(events.at(i).get_name() == event_name){
			return i;
		}
	}

	return -1;
}

//Returns the index for all upcoming events from the current date
int get_future_events_index(Date const& d){

	for(int i = 0; i < this.events.size(); ++i){
		if(events.at(i).get_date() >= d){
			return i;
		}
	}

	//If no upcoming events are found, all the events are in the past and we should add new to the end
	return this.events.size();
}

std::ostream& operator<< (std::ostream& output, Calendar<T> const& cal){

	for(int i = 0; i < this.events.size(); ++i){
		output << this.events.at(i) << std::endl;
	}

	return output;
}

//Initializes the calendar with current date
template <typename T>
Calendar<T>::Calendar() {
	current_date = new T();
}

//Initializes the calendar with a given date
template <typename T, typename S>
Calendar<T>::Calendar(S const& rhs) {
	current_date = rhs;
}

//Destructor
template <typename T>
Calendar<T>::~Calendar(){
	delete current_date;

	//TODO check if works, arrayoutofbounds if not
	for (int i = 0; i < events.size(); ++i){
		events.erase(events.begin() + i);
	}

	delete [] events;
}