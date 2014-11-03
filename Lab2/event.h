#ifndef EVENT_H
#define EVENT_H

#include "date.h"
#include <string>

namespace lab2 {
    class Event {
    private:
        std::string name;
        Date * date;
    public:
        std::string get_name();
        Date& get_date(); 
        friend std::ostream& operator<< (std::ostream&, Event const&);

        Event(std::string const&, Date&);
        ~Event();
    };
}

#endif // EVENT_H

namespace lab2 {

    std::string Event::get_name(){
        return name;
    }

    Date& Event::get_date(){
        return *date;
    }

    std::ostream& operator<< (std::ostream& output, Event const& ev){
        output << ev.name << " : " << *ev.date;

        return output;
    }

    Event::Event(std::string const& n, Date& d){
        name = n;
        date = &d;
    }

    Event::~Event(){
    }
}