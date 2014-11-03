#ifndef CALENDAR_H
#define CALENDAR_H


class Calendar {
private:
	Date & current_date;
	//TODO data structure that contains both an event (string) and a Date

public:
	Calendar(); //Initializes with current date
	Calendar(Date const&)

	bool set_date(int, int, int);
	bool add_event(std::string, int, int, int);
	bool is_valid_date(int, int, int);
	bool event_exists(std::string, int, int, int);
};

#endif // CALENDAR_H

//Sets the date of the calendar
bool set_date(int year, int month, int day){
	
	if(!is_valid_date(year, month, day)){
		return false;
	}

	//current_date = TODO

	return true;
}

//Adds an event to the calendar given that the date is valid and the event doesn't already exist
bool add_event(std::string event, int year, int month, int day){
	
	if(!is_valid_date(year, month, day)){
		return false;
	}

	if(event_exists(event, year, month, day)){
		return false;
	}

	//TODO add event

	return true;
}

//Removes an event from the calendar given that it exists
bool remove_event(std::string event, int year, int month, int day){
	
	if(!event_exists(event, year, month, day)){
		return false;
	}

	//TODO remove event

	return true;
}

//Check whether the date is valid
bool is_valid_date(int year, int month, int day){

	//TODO check

	return true;
}

//Checks whether the event exists
bool event_exists(std::string event, int year, int month, int day){

	//TODO check

	return true;
}

//Initializes the calendar with current date
Calendar::Calendar() {
	//current_date = TODO
}

//Initializes the calendar with a given date
Calendar::Calendar(Date const& rhs) {
	current_date = rhs;
}