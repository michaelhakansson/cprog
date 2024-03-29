#ifndef CALENDAR_H
#define CALENDAR_H

#include "event.h"
#include <vector>
#include <iostream>
#include <sstream>      // Stringstream

namespace lab2 {
    template <typename T> class Calendar {
    public:
        T current_date;
        std::vector<Event<T> > events;

        /*
         * The available calendar formats
         */
        enum format {list, cal, iCalendar};
        
        /**
         * Returns the current format of the calendar
         * @return The current format
         */
        format get_format() const;

        /**
         * Sets the format of the calendar
         * @param f The wanted format. The format must be in the
         *          enum format list.
         */
        void set_format(format f);

        bool set_date(int year, int month, int day);

        bool add_event(std::string);
        bool add_event(std::string, int);
        bool add_event(std::string, int, int);
        bool add_event(std::string, int, int, int);

        bool remove_event(std::string);
        bool remove_event(std::string, int);
        bool remove_event(std::string, int, int);
        bool remove_event(std::string, int, int, int);

        bool has_event_on_date(int year, int month, int day) const;

        int get_future_events_index() const;
        int get_future_events_index(T const&) const;
        bool is_valid_date(int, int, int) const;
        int event_exists(std::string, int, int, int) const;

        template <typename F>
        friend std::ostream& operator<< (std::ostream&, Calendar<F> const&);

        Calendar(); //Initializes with current date
        template <typename S>
        Calendar(Calendar<S> const&);
    private:
        format current_format = list;
    };
}

#include <stdexcept>

namespace lab2 {
    template <typename T>
    typename Calendar<T>::format Calendar<T>::get_format() const {
        return current_format;
    }

    template <typename T>
    void Calendar<T>::set_format(format f) {
        current_format = f;
    }

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
            T(year, month, day);
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

    template <typename T>
    bool Calendar<T>::has_event_on_date(int year, int month, int day) const {
        T compare_to_date = T(year, month, day);
        for(int i = 0; i < events.size(); ++i) {
            if (events.at(i).get_date() == compare_to_date) {
                return true;
            }
        }
        return false;
    }


    /**
     * Returns an ostream in the current format of the calendar.
     */
    template <typename F>
    std::ostream& operator<< (std::ostream& output, Calendar<F> const& cal){
        switch (cal.get_format()) {
            case 0: // list
                list_output(output, cal);
                break;
            case 1: // cal
                cal_output(output, cal);
                break;
            case 2: // iCalendar
                icalendar_output(output, cal);
                break;
            default:
                break;
        }
        return output;
    }
    
    /**
     * Helper function for operator<<.
     * Modifies the referenced to ostream so that it corresponds to the list
     * view.
     */
    template <typename F>
    void list_output(std::ostream& output, Calendar<F> const& cal) {
        for(int i = cal.get_future_events_index(); i < cal.events.size(); ++i){
            output << cal.events.at(i) << std::endl;
        }
    }

    /**
     * Helper function for cal_output.
     * Returns the week day number (1=monday, 7=sunday) for the first
     * day of the month.
     */
    int week_day_number_first_day_of_month(int day_date, int current_week_day) {
        int res = current_week_day - ( (day_date-1) % 7);
            return (res <= 0 ? res + 7 : res);
    }

    /**
     * Helper function for operator<<.
     * Modifies the referenced to ostream so that it corresponds to the cal
     * view.
     */
    template <typename F>
    void cal_output(std::ostream& output, Calendar<F> const& cal) {
        int cal_width = 35;
        std::string year = std::to_string( cal.current_date.year() );
        std::string month_name = cal.current_date.month_name();
        
        // Number of spaces before month name
        for (int i = 0; i < 0.5*(cal_width - ( month_name.length() + 1 + year.length()) ); ++i) {
            output << " ";
        }
        
        // Print the month name and year
        output << month_name << " " << year << std::endl;

        // Print the day names
        output << " må   " << "ti   " << "on   " << "to   " << "fr   " << "lö   " << "sö  " << std::endl;

        // The current week day number
        int wdn = week_day_number_first_day_of_month(cal.current_date.day(), cal.current_date.week_day());

        // Print leading spaces for first day of the month
        for (int j = 1; j < wdn; ++j) { // The spaces before the first day in the month
            output << "     ";
        }

        // Printing all days
        for (int i = 1; i <= cal.current_date.days_this_month(); ++i) {
            bool has_event = cal.has_event_on_date(cal.current_date.year(), cal.current_date.month(), i);

            if (wdn > cal.current_date.days_per_week()) { // New line
                output << std::endl;
                wdn = 1;
            }

            if (i == cal.current_date.day()) { // Current day
                if (i < 10) { // Single digit date
                    if (has_event) {
                        output << "<" << i << "*> ";
                    } else { // Has no event
                        output << "< " << i << "> ";
                    }
                } else { // Two digit date
                    if (has_event) {
                        output << "<" << i << "*>";
                    } else { // Has no event
                        output << "<" << i << "> ";
                    }
                    
                }
                ++wdn;
            } else { // Not the current day
                if (i < 10) { // Single digit date
                    if (has_event) {
                        output << " " << i << "*  ";
                    } else { // Has no event
                        output << "  " << i << "  ";
                    }
                } else { // Two digit date
                    if (has_event) {
                        output << " " << i << "* ";
                    } else { // Has no event
                        output << " " << i << "  ";
                    }
                }
                ++wdn;
            }
        }

        output << std::endl << std::endl;
        F first_date_of_month = F(cal.current_date.year(), cal.current_date.month(), 1);
        F last_date_of_month = F(cal.current_date.year(), cal.current_date.month(), cal.current_date.days_this_month());
        
        for(int i = 0; i < cal.events.size() && cal.events.at(i).get_date() <= last_date_of_month; ++i) {
            if (cal.events.at(i).get_date() >= first_date_of_month) {
                output << "  " << cal.events.at(i).get_date() << ": " << cal.events.at(i).get_name() << std::endl;    
            }
            
        }

    }

    /**
     * Helper function for operator<<.
     * Modifies the referenced to ostream so that it corresponds to the
     * iCalendar view.
     */
    template <typename F>
    void icalendar_output(std::ostream& output, Calendar<F> const& cal) {
        
        // Calendar info
        output << "BEGIN:VCALENDAR" << std::endl
               << "VERSION:2.0" << std::endl
               << "PRODID:-//KalleKalender"
               << std::endl;

        // Each event
        for(int i = 0; i < cal.events.size(); ++i){
            Event<F> event = cal.events.at(i);
            F date = event.get_date();
            int month = date.month();
            int day  = date.day();
            output << "BEGIN:VEVENT" << std::endl
                   << "DTSTART:" << date.year()
                                 << (month < 10 ? "0" : "") << month
                                 << (day < 10 ? "0" : "") << day
                                 << "T080000" << std::endl
                   << "DTEND:"   << date.year()
                                 << (month < 10 ? "0" : "") << month
                                 << (day < 10 ? "0" : "") << day
                                 << "T090000" << std::endl

                   << "SUMMARY:" << event.get_name() << std::endl
                   << "END:VEVENT" << std::endl;

        }

        // End of calendar
        output << "END:VCALENDAR" << std::endl;

    }
}

#endif // CALENDAR_H


