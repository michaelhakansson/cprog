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
    assert(g.get_current_date().year() == 2012);
    assert(g.get_current_date().month() == 12);
    assert(g.get_current_date().day() == 13);

    g.set_date(2014,1,1);
    assert(g.get_current_date().year() == 2014);
    assert(g.get_current_date().month() == 1);
    assert(g.get_current_date().day() == 1);
}


{
    std::cout << "Testing output operator" << std::endl;
    Calendar<Gregorian> cal;
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


std::cout << "All tests passed!" << std::endl;
std::cout << "----------------------------------------" << std::endl;

return 0;
}

