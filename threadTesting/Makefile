CPPFLAGS=-std=c++11 -pthread -g
LDFLAGS=-g

spydr: spydr.o schedule.o
	g++ $(CPPFLAGS) -o spydr spydr.o schedule.o

spydr.o: spydr.cpp schedule.o
	g++ $(CPPFLAGS) -c spydr.cpp

schedule.o: schedule.cpp program.h schedule.h
	g++ $(CPPFLAGS) -c schedule.cpp

test: threadTest.o
	g++ $(CPPFLAGS) -o test threadTest.o

threadTest.o: threadTest.cpp schedule.cpp
	g++ $(CPPFLAGS) -c threadTest.cpp schedule.cpp program.h schedule.h -o threadTest.o

clean:
	rm -f *.o
