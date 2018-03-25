CPPFLAGS=-std=c++11 -pthread -g
LDFLAGS=-g

spydr: spydr.o
	g++ $(CPPFLAGS) -o spydr spydr.o

spydr.o: spydr.cpp program.h schedule.cpp schedule.h
	g++ $(CPPFLAGS) -o spydr.o spydr.cpp schedule.cpp program.h schedule.h

test: threadTest.o
	g++ $(CPPFLAGS) -o test threadTest.o

threadTest.o: threadTest.cpp schedule.cpp
	g++ $(CPPFLAGS) -c threadTest.cpp schedule.cpp program.h schedule.h

clean:
	rm *.o spydr test
