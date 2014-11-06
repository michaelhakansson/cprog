// projektlokala headerfiler
#include "kattistime.h"     
#include "gregorian.h"
#include "julian.h"
#include "calendar.h"

// STL headerfiler
#include <iostream>
#include <sstream>              // std::stringstream
#include <assert.h>             // assert(b) ger felmeddelande om b falsk


int main()
{
    using namespace lab2;        // Exponera funktionalitet i namnrymden lab2

    ////////////////////////////////////////////////////////////
    // Satt tiden. OBS skicka inte nedanstaende kod till kattis
    time_t mytime;
    time(&mytime);
    set_k_time(mytime);
    ////////////////////////////////////////////////////////////

std::cout << "----------------------------------------" << std::endl;
std::cout << "Initiating tests" << std::endl;

{
    std::cout << "Testing default constructor and event_exists" << std::endl;
    Calendar<Gregorian> g;
    g.set_date(2014,11,3);
    assert(g.add_event("Todays date G") == true);
    assert(g.event_exists("Todays date G", 2014, 11, 3) != -1); // Should exist
    assert(g.event_exists("Todays date G", 2014, 11, 4) == -1); // Shouldn't exist

    Calendar<Julian> j;
    j.set_date(2014,11,3);
    assert(j.add_event("Todays date J") == true);
    assert(j.event_exists("Todays date J", 2014, 11, 3) != -1); // Should exist
}

{
    std::cout << "Testing different types of constructors" << std::endl;
    Calendar<Gregorian> g;
    g.set_date(2014,11,3);
    g.add_event("Date1", 1);
    g.add_event("Date2", 2,10);
    g.add_event("Date3", 3,11,2001);
    assert(g.event_exists("Date1", 2014, 11, 1) != -1); // Should exist
    assert(g.event_exists("Date2", 2014, 10, 2) != -1); // Should exist
    assert(g.event_exists("Date3", 2001, 11, 3) != -1); // Should exist
    assert(g.add_event("Invalid", 29,2,2001) == false); // Shlouldn't work

    Calendar<Julian> j;
    j.set_date(2014,11,3);
    j.add_event("Date1", 1);
    j.add_event("Date2", 2,10);
    j.add_event("Date3", 3,11,2001);
    assert(j.event_exists("Date1", 2014, 11, 1) != -1); // Should exist
    assert(j.event_exists("Date2", 2014, 10, 2) != -1); // Should exist
    assert(j.event_exists("Date3", 2001, 11, 3) != -1); // Should exist
}


{
    std::cout << "Testing copy constructor" << std::endl;
    Calendar<Gregorian> g;
    g.set_date(2014,11,3);
    g.add_event("Date1", 1);
    g.add_event("Date2", 2,10);
    g.add_event("Date3", 3,11,2001);

    Calendar<Julian> j = g;
    assert(j.event_exists("Date1", 2014, 10, 19) != -1); // Should exist
    assert(j.event_exists("Date2", 2014, 9, 19) != -1); // Should exist
    assert(j.event_exists("Date3", 2001, 10, 21) != -1); // Should exist
}

{
    std::cout << "Testing remove event" << std::endl;
    Calendar<Gregorian> g;
    g.set_date(2014,11,3);

    assert(g.event_exists("Todays date G", 2014, 11, 3) == -1); // Shouldn't exist

    g.add_event("Todays date G");
    g.add_event("Date1", 1);
    g.add_event("Date2", 2,10);
    g.add_event("Date3", 3,11,2001);
    assert(g.event_exists("Todays date G", 2014, 11, 3) != -1); // Should exist
    assert(g.event_exists("Date1", 2014, 11, 1) != -1); // Should exist
    assert(g.event_exists("Date2", 2014, 10, 2) != -1); // Should exist
    assert(g.event_exists("Date3", 2001, 11, 3) != -1); // Should exist

    assert(g.remove_event("Date1", 2) == false); // Doesn't exist with this day
    assert(g.event_exists("Date1", 2014, 11, 1) != -1); // Should exist
    assert(g.remove_event("Todays date G") == true);
    assert(g.remove_event("Date1", 1) == true);
    assert(g.remove_event("Date2", 2,10) == true);
    assert(g.remove_event("Date3", 3,11,2001) == true);
    assert(g.event_exists("Todays date G", 2014, 11, 3) == -1); // Should exist
    assert(g.event_exists("Date1", 2014, 11, 1) == -1); // Shouldn't exist
    assert(g.event_exists("Date2", 2014, 10, 2) == -1); // Shouldn't exist
    assert(g.event_exists("Date3", 2001, 11, 3) == -1); // Shouldn't exist
}


{
    std::cout << "Testing get_future_events_index" << std::endl;
    Calendar<Gregorian> g;
    g.set_date(2014,11,5);
    g.add_event("Hej0", 1,1,2000);  // Index 0
    g.add_event("Hej1", 1,1,2001);  // Index 1
    g.add_event("Hej2", 1,1,2014);  // Index 2
    g.add_event("Hej3");            // Index 3 <-- Current day
    g.add_event("Hej4");            // Index 4 <-- Current day
    g.add_event("Hej5", 6,11,2014); // Index 5 <-- Future index
    g.add_event("Hej7", 7,11,2014); // Index 6
    g.add_event("Hej6", 1,1,2015);  // Index 7
    assert(g.get_future_events_index() == 5);

    Calendar<Julian> j;
    j.set_date(2014,11,5);
    j.add_event("Hej0", 1,1,2000);    // Index 0
    j.add_event("Hej1", 1,1,2001);    // Index 1
    j.remove_event("Hej1", 1,1,2001); // Index 1 removed
    j.add_event("Hej2", 1,1,2014);    // Index 1
    j.add_event("Hej3");              // Index 2 <-- Current day
    j.add_event("Hej4");              // Index 3 <-- Current day
    j.add_event("Hej5", 6,11,2014);   // Index 4 <-- Future index
    j.add_event("Hej7", 7,11,2014);   // Index 5
    j.add_event("Hej6", 1,1,2015);    // Index 6
    assert(j.get_future_events_index() == 4);
}

{
    std::cout << "Testing is_valid_date" << std::endl;
    Calendar<Gregorian> g;
    assert(g.is_valid_date(2000,01,30) == true);
    assert(g.is_valid_date(2000,02,29) == true);
    assert(g.is_valid_date(1900,02,29) == false);
    assert(g.is_valid_date(2001,02,29) == false);
    assert(g.is_valid_date(2000,02,30) == false);
    assert(g.is_valid_date(2000,11,32) == false);

    Calendar<Julian> j;
    assert(j.is_valid_date(2000,01,30) == true);
    assert(j.is_valid_date(2000,02,29) == true);
    assert(j.is_valid_date(1900,02,29) == true);
    assert(j.is_valid_date(2001,02,29) == false);
    assert(j.is_valid_date(2000,02,30) == false);
    assert(j.is_valid_date(2000,11,32) == false);
}

{
    std::cout << "Testing set_date" << std::endl;
    Calendar<Gregorian> g;
    g.set_date(2012,12,13);
    assert(g.current_date.year() == 2012);
    assert(g.current_date.month() == 12);
    assert(g.current_date.day() == 13);

    g.set_date(2014,1,1);
    assert(g.current_date.year() == 2014);
    assert(g.current_date.month() == 1);
    assert(g.current_date.day() == 1);
}

{
    std::cout << "Testing format and set_format" << std::endl;
    Calendar<Gregorian> g;
    assert(g.get_format() == 0);
    g.set_format(Calendar<Gregorian>::cal);
    assert(g.get_format() == 1);
    g.set_format(Calendar<Gregorian>::iCalendar);
    assert(g.get_format() == 2);
}

{
    std::cout << "Testing output operator (list)" << std::endl;
    Calendar<Gregorian> cal;
    assert(cal.get_format() == 0);
    std::stringstream ss1;
    std::stringstream ss1_expected;
    std::stringstream ss2;
    std::stringstream ss2_expected;

    cal.set_date(2000, 12, 2);
    cal.add_event("Baskettraning", 4, 12, 2000);
    cal.add_event("Baskettraning", 11, 12, 2000);
    cal.add_event("Nyarsfrukost", 1, 1, 2001);
    cal.add_event("Forsta advent", 1);          // ar = 2000, manad = 12
    cal.add_event("Vardagjamning", 20, 3);      // ar = 2000
    cal.add_event("Julafton", 24, 12);
    cal.add_event("Kalle Anka halsar god jul", 24); // ocksa pa julafton
    cal.add_event("Julafton", 24); // En likadan handelse samma datum ska
                                 // ignoreras och inte sattas in i kalendern
    cal.add_event("Min forsta cykel", 20, 12, 2000);
    cal.remove_event("Baskettraning", 4);
    ss1 << cal;


    cal.remove_event("Vardagjamning", 20, 3, 2000);
    cal.remove_event("Kalle Anka halsar god jul", 24, 12, 2000);
    cal.set_date(2000, 11, 2);
    cal.remove_event("Julafton", 24);    
    ss2 << cal;

    ss1_expected << "2000-12-11 : Baskettraning" << std::endl;
    ss1_expected << "2000-12-20 : Min forsta cykel" << std::endl;
    ss1_expected << "2000-12-24 : Julafton" << std::endl;
    ss1_expected << "2000-12-24 : Kalle Anka halsar god jul" << std::endl;
    ss1_expected << "2001-01-01 : Nyarsfrukost" << std::endl;

    ss2_expected << "2000-12-01 : Forsta advent" << std::endl;
    ss2_expected << "2000-12-11 : Baskettraning" << std::endl;
    ss2_expected << "2000-12-20 : Min forsta cykel" << std::endl;
    ss2_expected << "2000-12-24 : Julafton" << std::endl;
    ss2_expected << "2001-01-01 : Nyarsfrukost" << std::endl;

    assert(ss1.str() == ss1_expected.str());
    assert(ss2.str() == ss2_expected.str());
}

{
    std::cout << "Testing output operator (cal)" << std::endl;
    Calendar<Gregorian> g;
    g.set_date(2007,12,2);
    g.add_event("Min andra cykel",20);
    g.add_event("Julafton",24);
    std::cout << g << std::endl;
    g.set_format(Calendar<Gregorian>::cal);
    std::cout << g << std::endl;
    g.set_date(2014,10,30);
    std::cout << g << std::endl;

    g.set_date(2014,01,13);
    g.add_event("HEJ", 13,1,2014);
    g.add_event("HEJ", 14,1,2014);
    g.add_event("HEJ", 14,1,2015);
    g.add_event("HEJ", 31,1,2014);
    g.add_event("HEJ", 1,2,2014);
    std::cout << g << std::endl;
    g.set_date(2014,01,7);
    std::cout << g << std::endl;

    // TODO: Skriv faktiska tester
}

{
    std::cout << "Testing output operator (iCalendar)" << std::endl;
    // TODO
}

// TODO: Test has_event_on_date()

{
    std::cout << "week_day_number_first_day_of_month" << std::endl;
    assert(week_day_number_first_day_of_month(1, 1) == 1);
    assert(week_day_number_first_day_of_month(1, 2) == 2);
    assert(week_day_number_first_day_of_month(1, 3) == 3);
    assert(week_day_number_first_day_of_month(1, 4) == 4);
    assert(week_day_number_first_day_of_month(1, 5) == 5);
    assert(week_day_number_first_day_of_month(1, 6) == 6);
    assert(week_day_number_first_day_of_month(1, 7) == 7);
    
    assert(week_day_number_first_day_of_month(2, 1) == 7);
    assert(week_day_number_first_day_of_month(2, 2) == 1);
    assert(week_day_number_first_day_of_month(2, 3) == 2);
    assert(week_day_number_first_day_of_month(2, 4) == 3);
    assert(week_day_number_first_day_of_month(2, 5) == 4);
    assert(week_day_number_first_day_of_month(2, 6) == 5);
    assert(week_day_number_first_day_of_month(2, 7) == 6);

    assert(week_day_number_first_day_of_month(3, 1) == 6);
    assert(week_day_number_first_day_of_month(3, 2) == 7);
    assert(week_day_number_first_day_of_month(3, 3) == 1);
    assert(week_day_number_first_day_of_month(3, 4) == 2);
    assert(week_day_number_first_day_of_month(3, 5) == 3);
    assert(week_day_number_first_day_of_month(3, 6) == 4);
    assert(week_day_number_first_day_of_month(3, 7) == 5);

    assert(week_day_number_first_day_of_month(4, 1) == 5);
    assert(week_day_number_first_day_of_month(4, 2) == 6);
    assert(week_day_number_first_day_of_month(4, 3) == 7);
    assert(week_day_number_first_day_of_month(4, 4) == 1);
    assert(week_day_number_first_day_of_month(4, 5) == 2);
    assert(week_day_number_first_day_of_month(4, 6) == 3);
    assert(week_day_number_first_day_of_month(4, 7) == 4);

    assert(week_day_number_first_day_of_month(5, 1) == 4);
    assert(week_day_number_first_day_of_month(5, 2) == 5);
    assert(week_day_number_first_day_of_month(5, 3) == 6);
    assert(week_day_number_first_day_of_month(5, 4) == 7);
    assert(week_day_number_first_day_of_month(5, 5) == 1);
    assert(week_day_number_first_day_of_month(5, 6) == 2);
    assert(week_day_number_first_day_of_month(5, 7) == 3);

    assert(week_day_number_first_day_of_month(6, 1) == 3);
    assert(week_day_number_first_day_of_month(6, 2) == 4);
    assert(week_day_number_first_day_of_month(6, 3) == 5);
    assert(week_day_number_first_day_of_month(6, 4) == 6);
    assert(week_day_number_first_day_of_month(6, 5) == 7);
    assert(week_day_number_first_day_of_month(6, 6) == 1);
    assert(week_day_number_first_day_of_month(6, 7) == 2);

    assert(week_day_number_first_day_of_month(7, 1) == 2);
    assert(week_day_number_first_day_of_month(7, 2) == 3);
    assert(week_day_number_first_day_of_month(7, 3) == 4);
    assert(week_day_number_first_day_of_month(7, 4) == 5);
    assert(week_day_number_first_day_of_month(7, 5) == 6);
    assert(week_day_number_first_day_of_month(7, 6) == 7);
    assert(week_day_number_first_day_of_month(7, 7) == 1);

    assert(week_day_number_first_day_of_month(8, 1) == 1);
    assert(week_day_number_first_day_of_month(8, 2) == 2);
    assert(week_day_number_first_day_of_month(8, 3) == 3);
    assert(week_day_number_first_day_of_month(8, 4) == 4);
    assert(week_day_number_first_day_of_month(8, 5) == 5);
    assert(week_day_number_first_day_of_month(8, 6) == 6);
    assert(week_day_number_first_day_of_month(8, 7) == 7);
    
    assert(week_day_number_first_day_of_month(9, 1) == 7);
    assert(week_day_number_first_day_of_month(9, 2) == 1);
    assert(week_day_number_first_day_of_month(9, 3) == 2);
    assert(week_day_number_first_day_of_month(9, 4) == 3);
    assert(week_day_number_first_day_of_month(9, 5) == 4);
    assert(week_day_number_first_day_of_month(9, 6) == 5);
    assert(week_day_number_first_day_of_month(9, 7) == 6);

    assert(week_day_number_first_day_of_month(10, 1) == 6);
    assert(week_day_number_first_day_of_month(10, 2) == 7);
    assert(week_day_number_first_day_of_month(10, 3) == 1);
    assert(week_day_number_first_day_of_month(10, 4) == 2);
    assert(week_day_number_first_day_of_month(10, 5) == 3);
    assert(week_day_number_first_day_of_month(10, 6) == 4);
    assert(week_day_number_first_day_of_month(10, 7) == 5);

    assert(week_day_number_first_day_of_month(11, 1) == 5);
    assert(week_day_number_first_day_of_month(11, 2) == 6);
    assert(week_day_number_first_day_of_month(11, 3) == 7);
    assert(week_day_number_first_day_of_month(11, 4) == 1);
    assert(week_day_number_first_day_of_month(11, 5) == 2);
    assert(week_day_number_first_day_of_month(11, 6) == 3);
    assert(week_day_number_first_day_of_month(11, 7) == 4);

    assert(week_day_number_first_day_of_month(12, 1) == 4);
    assert(week_day_number_first_day_of_month(12, 2) == 5);
    assert(week_day_number_first_day_of_month(12, 3) == 6);
    assert(week_day_number_first_day_of_month(12, 4) == 7);
    assert(week_day_number_first_day_of_month(12, 5) == 1);
    assert(week_day_number_first_day_of_month(12, 6) == 2);
    assert(week_day_number_first_day_of_month(12, 7) == 3);

    assert(week_day_number_first_day_of_month(13, 1) == 3);
    assert(week_day_number_first_day_of_month(13, 2) == 4);
    assert(week_day_number_first_day_of_month(13, 3) == 5);
    assert(week_day_number_first_day_of_month(13, 4) == 6);
    assert(week_day_number_first_day_of_month(13, 5) == 7);
    assert(week_day_number_first_day_of_month(13, 6) == 1);
    assert(week_day_number_first_day_of_month(13, 7) == 2);

    assert(week_day_number_first_day_of_month(14, 1) == 2);
    assert(week_day_number_first_day_of_month(14, 2) == 3);
    assert(week_day_number_first_day_of_month(14, 3) == 4);
    assert(week_day_number_first_day_of_month(14, 4) == 5);
    assert(week_day_number_first_day_of_month(14, 5) == 6);
    assert(week_day_number_first_day_of_month(14, 6) == 7);
    assert(week_day_number_first_day_of_month(14, 7) == 1);

    assert(week_day_number_first_day_of_month(15, 1) == 1);
    assert(week_day_number_first_day_of_month(15, 2) == 2);
    assert(week_day_number_first_day_of_month(15, 3) == 3);
    assert(week_day_number_first_day_of_month(15, 4) == 4);
    assert(week_day_number_first_day_of_month(15, 5) == 5);
    assert(week_day_number_first_day_of_month(15, 6) == 6);
    assert(week_day_number_first_day_of_month(15, 7) == 7);
    
    assert(week_day_number_first_day_of_month(16, 1) == 7);
    assert(week_day_number_first_day_of_month(16, 2) == 1);
    assert(week_day_number_first_day_of_month(16, 3) == 2);
    assert(week_day_number_first_day_of_month(16, 4) == 3);
    assert(week_day_number_first_day_of_month(16, 5) == 4);
    assert(week_day_number_first_day_of_month(16, 6) == 5);
    assert(week_day_number_first_day_of_month(16, 7) == 6);

    assert(week_day_number_first_day_of_month(17, 1) == 6);
    assert(week_day_number_first_day_of_month(17, 2) == 7);
    assert(week_day_number_first_day_of_month(17, 3) == 1);
    assert(week_day_number_first_day_of_month(17, 4) == 2);
    assert(week_day_number_first_day_of_month(17, 5) == 3);
    assert(week_day_number_first_day_of_month(17, 6) == 4);
    assert(week_day_number_first_day_of_month(17, 7) == 5);

    assert(week_day_number_first_day_of_month(18, 1) == 5);
    assert(week_day_number_first_day_of_month(18, 2) == 6);
    assert(week_day_number_first_day_of_month(18, 3) == 7);
    assert(week_day_number_first_day_of_month(18, 4) == 1);
    assert(week_day_number_first_day_of_month(18, 5) == 2);
    assert(week_day_number_first_day_of_month(18, 6) == 3);
    assert(week_day_number_first_day_of_month(18, 7) == 4);

    assert(week_day_number_first_day_of_month(19, 1) == 4);
    assert(week_day_number_first_day_of_month(19, 2) == 5);
    assert(week_day_number_first_day_of_month(19, 3) == 6);
    assert(week_day_number_first_day_of_month(19, 4) == 7);
    assert(week_day_number_first_day_of_month(19, 5) == 1);
    assert(week_day_number_first_day_of_month(19, 6) == 2);
    assert(week_day_number_first_day_of_month(19, 7) == 3);

    assert(week_day_number_first_day_of_month(20, 1) == 3);
    assert(week_day_number_first_day_of_month(20, 2) == 4);
    assert(week_day_number_first_day_of_month(20, 3) == 5);
    assert(week_day_number_first_day_of_month(20, 4) == 6);
    assert(week_day_number_first_day_of_month(20, 5) == 7);
    assert(week_day_number_first_day_of_month(20, 6) == 1);
    assert(week_day_number_first_day_of_month(20, 7) == 2);

    assert(week_day_number_first_day_of_month(21, 1) == 2);
    assert(week_day_number_first_day_of_month(21, 2) == 3);
    assert(week_day_number_first_day_of_month(21, 3) == 4);
    assert(week_day_number_first_day_of_month(21, 4) == 5);
    assert(week_day_number_first_day_of_month(21, 5) == 6);
    assert(week_day_number_first_day_of_month(21, 6) == 7);
    assert(week_day_number_first_day_of_month(21, 7) == 1);

    assert(week_day_number_first_day_of_month(22, 1) == 1);
    assert(week_day_number_first_day_of_month(22, 2) == 2);
    assert(week_day_number_first_day_of_month(22, 3) == 3);
    assert(week_day_number_first_day_of_month(22, 4) == 4);
    assert(week_day_number_first_day_of_month(22, 5) == 5);
    assert(week_day_number_first_day_of_month(22, 6) == 6);
    assert(week_day_number_first_day_of_month(22, 7) == 7);
    
    assert(week_day_number_first_day_of_month(23, 1) == 7);
    assert(week_day_number_first_day_of_month(23, 2) == 1);
    assert(week_day_number_first_day_of_month(23, 3) == 2);
    assert(week_day_number_first_day_of_month(23, 4) == 3);
    assert(week_day_number_first_day_of_month(23, 5) == 4);
    assert(week_day_number_first_day_of_month(23, 6) == 5);
    assert(week_day_number_first_day_of_month(23, 7) == 6);

    assert(week_day_number_first_day_of_month(24, 1) == 6);
    assert(week_day_number_first_day_of_month(24, 2) == 7);
    assert(week_day_number_first_day_of_month(24, 3) == 1);
    assert(week_day_number_first_day_of_month(24, 4) == 2);
    assert(week_day_number_first_day_of_month(24, 5) == 3);
    assert(week_day_number_first_day_of_month(24, 6) == 4);
    assert(week_day_number_first_day_of_month(24, 7) == 5);

    assert(week_day_number_first_day_of_month(25, 1) == 5);
    assert(week_day_number_first_day_of_month(25, 2) == 6);
    assert(week_day_number_first_day_of_month(25, 3) == 7);
    assert(week_day_number_first_day_of_month(25, 4) == 1);
    assert(week_day_number_first_day_of_month(25, 5) == 2);
    assert(week_day_number_first_day_of_month(25, 6) == 3);
    assert(week_day_number_first_day_of_month(25, 7) == 4);

    assert(week_day_number_first_day_of_month(26, 1) == 4);
    assert(week_day_number_first_day_of_month(26, 2) == 5);
    assert(week_day_number_first_day_of_month(26, 3) == 6);
    assert(week_day_number_first_day_of_month(26, 4) == 7);
    assert(week_day_number_first_day_of_month(26, 5) == 1);
    assert(week_day_number_first_day_of_month(26, 6) == 2);
    assert(week_day_number_first_day_of_month(26, 7) == 3);

    assert(week_day_number_first_day_of_month(27, 1) == 3);
    assert(week_day_number_first_day_of_month(27, 2) == 4);
    assert(week_day_number_first_day_of_month(27, 3) == 5);
    assert(week_day_number_first_day_of_month(27, 4) == 6);
    assert(week_day_number_first_day_of_month(27, 5) == 7);
    assert(week_day_number_first_day_of_month(27, 6) == 1);
    assert(week_day_number_first_day_of_month(27, 7) == 2);

    assert(week_day_number_first_day_of_month(28, 1) == 2);
    assert(week_day_number_first_day_of_month(28, 2) == 3);
    assert(week_day_number_first_day_of_month(28, 3) == 4);
    assert(week_day_number_first_day_of_month(28, 4) == 5);
    assert(week_day_number_first_day_of_month(28, 5) == 6);
    assert(week_day_number_first_day_of_month(28, 6) == 7);
    assert(week_day_number_first_day_of_month(28, 7) == 1);

    assert(week_day_number_first_day_of_month(29, 1) == 1);
    assert(week_day_number_first_day_of_month(29, 2) == 2);
    assert(week_day_number_first_day_of_month(29, 3) == 3);
    assert(week_day_number_first_day_of_month(29, 4) == 4);
    assert(week_day_number_first_day_of_month(29, 5) == 5);
    assert(week_day_number_first_day_of_month(29, 6) == 6);
    assert(week_day_number_first_day_of_month(29, 7) == 7);
    
    assert(week_day_number_first_day_of_month(30, 1) == 7);
    assert(week_day_number_first_day_of_month(30, 2) == 1);
    assert(week_day_number_first_day_of_month(30, 3) == 2);
    assert(week_day_number_first_day_of_month(30, 4) == 3);
    assert(week_day_number_first_day_of_month(30, 5) == 4);
    assert(week_day_number_first_day_of_month(30, 6) == 5);
    assert(week_day_number_first_day_of_month(30, 7) == 6);
}


std::cout << "All tests passed!" << std::endl;
std::cout << "----------------------------------------" << std::endl;

return 0;
}

