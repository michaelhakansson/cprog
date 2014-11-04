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

std::cout << "Testing default constructor" << std::endl;
Calendar<Gregorian> g;
Calendar<Julian> j;

g.set_date(2014,11,03);
assert(g.add_event("Todays date") == true);
assert(g.event_exists("Todays date", 2014, 11, 3) != -1); // Should exist
assert(g.event_exists("Todays date", 2014, 11, 4) == -1); // Shouldn't exist
// std::cout << g << std::endl;

assert(j.add_event("Todays date") == true);






std::cout << "All tests passed!" << std::endl;

    return 0;
}

