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

{
    std::cout << "Simple date 1" << std::endl;
    Gregorian g = Gregorian(1992, 05, 20);
    assert(g.year() == 1992 && g.month() == 05 && g.day() == 20);
    
    Julian j = g;
    assert(j.year() == 1992 && j.month() == 05 && j.day() == 07);

    assert(g.year() == 1992 && g.month() == 05 && g.day() == 20);
}

{
    std::cout << "Simple date 2" << std::endl;
    Julian j = Julian(1992, 05, 07);

    assert(j.year() == 1992 && j.month() == 05 && j.day() == 07);

    Gregorian g = j;
    assert(g.year() == 1992 && g.month() == 05 && g.day() == 20);
    assert(j.year() == 1992 && j.month() == 05 && j.day() == 07);
}

{
    std::cout << "Leap day 1" << std::endl;
    Gregorian g = Gregorian(1992, 02, 29);
    assert(g.year() == 1992 && g.month() == 02 && g.day() == 29);
    
    Julian j = g;
    assert(j.year() == 1992 && j.month() == 02 && j.day() == 16);

    assert(g.year() == 1992 && g.month() == 02 && g.day() == 29);
}

{
    std::cout << "Leap day 2" << std::endl;
    Julian j = Julian(1992, 02, 29);

    assert(j.year() == 1992 && j.month() == 02 && j.day() == 29);

    Gregorian g = j;
    assert(g.year() == 1992 && g.month() == 03 && g.day() == 13);
    assert(j.year() == 1992 && j.month() == 02 && j.day() == 29);
}

{
    std::cout << "New years eve 1" << std::endl;
    Gregorian g = Gregorian(1999, 12, 31);
    assert(g.year() == 1999 && g.month() == 12 && g.day() == 31);
    
    Julian j = g;
    assert(j.year() == 1999 && j.month() == 12 && j.day() == 18);

    assert(g.year() == 1999 && g.month() == 12 && g.day() == 31);
}

{
    std::cout << "New years eve 2" << std::endl;
    Julian j = Julian(1999, 12, 31);

    assert(j.year() == 1999 && j.month() == 12 && j.day() == 31);

    Gregorian g = j;
    assert(g.year() == 2000 && g.month() == 01 && g.day() == 13);
    assert(j.year() == 1999 && j.month() == 12 && j.day() == 31);
}

{
    std::cout << "New years day 1" << std::endl;
    Gregorian g = Gregorian(2000, 01, 01);
    assert(g.year() == 2000 && g.month() == 01 && g.day() == 01);
    
    Julian j = g;
    assert(j.year() == 1999 && j.month() == 12 && j.day() == 19);

    assert(g.year() == 2000 && g.month() == 01 && g.day() == 01);
}

{
    std::cout << "New years day 2" << std::endl;
    Julian j = Julian(2000, 01, 01);

    assert(j.year() == 2000 && j.month() == 01 && j.day() == 01);

    Gregorian g = j;
    assert(g.year() == 2000 && g.month() == 01 && g.day() == 14);
    assert(j.year() == 2000 && j.month() == 01 && j.day() == 01);
}


std::cout << "All tests passed!" << std::endl;

return 0;
}

