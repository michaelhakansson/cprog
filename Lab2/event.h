#ifndef EVENT_H
#define EVENT_H

#include "date.h"
#include <string>
#include <iostream>

namespace lab2 {
    class Event {
    private:
    public:
        std::string name;
        Date * date;
        std::string get_name() const;
        Date& get_date() const; 
        friend std::ostream& operator<< (std::ostream&, Event const&);

        Event(std::string const&, Date*);
        ~Event();
    };
}

#endif // EVENT_H

namespace lab2 {

    std::string Event::get_name() const {
        return name;
    }

    Date& Event::get_date() const {
        return *date;
    }

    std::ostream& operator<< (std::ostream& output, Event const& ev){
        output << *ev.date << " : " << ev.name;

        return output;
    }

    Event::Event(std::string const& n, Date* d){
        name = n;
        date = d;
    }

    Event::~Event(){
    }
}