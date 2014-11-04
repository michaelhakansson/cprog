#ifndef EVENT_H
#define EVENT_H

#include "date.h"
#include <string>
#include <iostream>

namespace lab2 {
    template <typename T> class Event {
    private:
    public:
        std::string name;
        T date;
        std::string get_name() const;
        T const& get_date() const;

        template <typename F>
        friend std::ostream& operator<< (std::ostream&, Event<F> const&);

        template <typename S>
        Event(std::string const&, S);
        ~Event();
    };
}

#endif // EVENT_H

namespace lab2 {

    template <typename T>
    std::string Event<T>::get_name() const {
        return name;
    }

    template <typename T>
    T const& Event<T>::get_date() const {
        return date;
    }

    template <typename F>
    std::ostream& operator<< (std::ostream& output, Event<F> const& ev){
        output << ev.date << " : " << ev.name;

        return output;
    }

    //Copy constructor
    template <typename T>
    template <typename S>
    Event<T>::Event(std::string const& n, S d){
        name = n;
        date = T(d);
    }

    //Destructor
    template <typename T>
    Event<T>::~Event(){
    }
}