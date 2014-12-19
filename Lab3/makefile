CC=g++
CDFLAGS= -std=c++11 -g -c -Wall
LDFLAGS=
SOURCES=character.cpp jonsson.cpp king.cpp spider.cpp world.cpp inventory.cpp container.cpp environment.cpp spiderroom.cpp item.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o) # Substitution variable that turns a list of *.cpp to *.o
EXECUTABLE=jonsson_league

all: $(SOURCES) $(EXECUTABLE)

# $@ expands to the file name of the target
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CDFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(EXECUTABLE)

run: all
	./$(EXECUTABLE)
