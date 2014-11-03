#ifndef CALENDAR_H
#define CALENDAR_H

#include "date.h"
#include "event.h"
#include <vector>

namespace lab2 {
	template <typename T> class Calendar {
	private:
		T & current_date;
		std::vector<Event> events;
	public:
		// Calendar& operator= (Calendar const&);

		bool set_date(int, int, int);

		bool add_event(std::string);
		bool add_event(std::string, int);
		bool add_event(std::string, int, int);
		bool add_event(std::string, int, int, int);

		bool remove_event(std::string);
		bool remove_event(std::string, int);
		bool remove_event(std::string, int, int);
		bool remove_event(std::string, int, int, int);

		int get_future_events_index(Date const&);
		bool is_valid_date(int, int, int);
		int event_exists(std::string, int, int, int);

		template <typename F>
		friend std::ostream& operator<< (std::ostream&, Calendar<F> const&);

		Calendar(); //Initializes with current date
		template <typename S>
		Calendar(S const&);
		~Calendar();
	};
}

#endif // CALENDAR_H
