#include "calendar.h"
#include <stdexcept>

namespace lab2 {

    // template <typename T>
    // Calendar<T>& Calendar<T>::operator= (Calendar<T> const& asd) {

    // }

    //Sets the date of the calendar
    template <typename T>
    bool Calendar<T>::set_date(int year, int month, int day){
        
        //The date is not valid and can't be set
        if(!is_valid_date(year, month, day)){
            return false;
        }

        current_date = new T(year, month, day);

        return true;
    }

    //Adds an event to the calendar given that the date is valid and the event doesn't already exist
    template <typename T>
    bool Calendar<T>::add_event(std::string event){
        return add_event(event, current_date.day(), current_date.month(), current_date.year());
    }

    template <typename T>
    bool Calendar<T>::add_event(std::string event, int day){
        return add_event(event, current_date.day(), current_date.month(), current_date.year());
    }

    template <typename T>
    bool Calendar<T>::add_event(std::string event, int day, int month){
        return add_event(event, current_date.day(), current_date.month(), current_date.year());
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
        Event ev = Event(event, d);

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
        return remove_event(event, current_date.day(), current_date.month(), current_date.year());
    }

    template <typename T>
    bool Calendar<T>::remove_event(std::string event, int day, int month){
        return remove_event(event, current_date.day(), current_date.month(), current_date.year());
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
    bool Calendar<T>::is_valid_date(int year, int month, int day){

        try{
            T test = T(year, month, day);
        } catch (std::out_of_range & e){
            return false;
        }

        return true;
    }

    //Checks whether an event with the same name exists
    template <typename T>
    int Calendar<T>::event_exists(std::string event_name, int year, int month, int day){

        //Returns the index where the event exists
        for(int i = 0; i < events.size(); ++i){
            if(events.at(i).get_name() == event_name){
                return i;
            }
        }

        return -1;
    }

    //Returns the index for all upcoming events from the current date
    template <typename T>
    int Calendar<T>::get_future_events_index(Date const& d){

        for(int i = 0; i < events.size(); ++i){
            if(events.at(i).get_date() >= d){
                return i;
            }
        }

        //If no upcoming events are found, all the events are in the past and we should add new to the end
        return events.size();
    }

    template <typename F>
    std::ostream& operator<< (std::ostream& output, Calendar<F> const& cal){

        for(int i = 0; i < cal.events.size(); ++i){
            output << cal.events.at(i) << std::endl;
        }

        return output;
    }

    //Initializes the calendar with current date
    template <typename T>
    Calendar<T>::Calendar() {
        current_date = new T();
    }

    //Initializes the calendar with a given date
    template <typename T>
    template <typename S>
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
}