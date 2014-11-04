// projektlokala headerfiler
#include "kattistime.h"     
#include "gregorian.h"
#include "julian.h"
#include "calendar.h"

// STL headerfiler
#include <iostream>
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


// Fran labpeket:
// std::cout << "----------------------------------------" << std::endl;
//   Calendar<Gregorian> cal;
//   cal.set_date(2000, 12, 2);
//   cal.add_event("Baskettraning", 4, 12, 2000);
//   cal.add_event("Baskettraning", 11, 12, 2000);
//   cal.add_event("Nyarsfrukost", 1, 1, 2001);
//   cal.add_event("Forsta advent", 1);          // ar = 2000, manad = 12
//   cal.add_event("Vardagjamning", 20, 3);      // ar = 2000
//   cal.add_event("Julafton", 24, 12);
//   cal.add_event("Kalle Anka halsar god jul", 24); // ocksa pa julafton
//   cal.add_event("Julafton", 24); // En likadan handelse samma datum ska
//                                  // ignoreras och inte sattas in i kalendern
//   cal.add_event("Min forsta cykel", 20, 12, 2000);
//   cal.remove_event("Baskettraning", 4);
//   std::cout << cal; // OBS! Vardagjamning och forsta advent ar
//                     // fore nuvarande datum och skrivs inte ut
//   std::cout << "----------------------------------------" << std::endl;
//   cal.remove_event("Vardagjamning", 20, 3, 2000);
//   cal.remove_event("Kalle Anka halsar god jul", 24, 12, 2000);
//   cal.set_date(2000, 11, 2);
//   if (! cal.remove_event("Julafton", 24)) {
//        std::cout << " cal.remove_event(\"Julafton\", 24) tar inte"<< std::endl
//                  << " bort nagot eftersom aktuell manad ar november" << std::endl;
//   }
//   std::cout << "----------------------------------------" << std::endl;
//   std::cout << cal;

/*
Forvantad output:
----------------------------------------
2000-12-11 : Baskettraaning
2000-12-20 : Min forsta cykel
2000-12-24 : Julafton
2000-12-24 : Kalle Anka halsar god jul
2001-01-01 : Nyarsfrukost
----------------------------------------
 cal.remove_event("Julafton", 24) tar inte
 bort nagot eftersom aktuell manad ar november
----------------------------------------
2000-12-01 : Forsta advent
2000-12-11 : Baskettraning
2000-12-20 : Min forsta cykel
2000-12-24 : Julafton
2001-01-01 : Nyarsfrukost
*/

{
    std::cout << "Testing default constructor" << std::endl;
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

    assert(j.event_exists("Date1", 2014, 10, 21) != -1); // Should exist
    assert(j.event_exists("Date2", 2014, 10, 19) != -1); // Should exist
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


std::cout << "All tests passed!" << std::endl;

return 0;
}

