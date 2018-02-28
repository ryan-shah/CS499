CPPFLAGS=-std=c++11 -pthread -g
LDFLAGS=-g

spydr: threadTest.o
	g++ $(CPPFLAGS) -o spydr threadTest.o

threadTest.o: threadTest.cpp program.h
	g++ $(CPPFLAGS) -c threadTest.cpp

clean:
	rm *.o spydr
