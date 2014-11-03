#ifndef EVENT_H
#define EVENT_H

class Event {
private:
    std::string name;
    Date & date;
public:
    std::string get_name();
    Date& get_date(); 
    friend std::ostream& operator<< (std::ostream&, Event const&);

    Event(std::string const&, Date const&);
    ~Event();
};

std::string get_name(){
    return name;
}

Date& get_date(){
    return date;
}

std::ostream& operator<< (std::ostream& output, Event const& ev){
    output << date << " : " << name;

    return output;
}

Event(std::string n, Date const& d){
    this.name = n;
    this.date = d;
}

~Event(){
    delete date;
}

#endif // EVENT_H