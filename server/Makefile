CPPFLAGS=-std=c++11 -pthread -g
LDFLAGS=-g

spydr: spydr.o schedule.o
	g++ $(CPPFLAGS) -o spydr spydr.o schedule.o

spydr.o: spydr.cpp schedule.o json.h
	g++ $(CPPFLAGS) -c spydr.cpp

schedule.o: schedule.cpp program.h schedule.h config.h
	g++ $(CPPFLAGS) -c schedule.cpp

clean:
	rm -f *.o spydr
