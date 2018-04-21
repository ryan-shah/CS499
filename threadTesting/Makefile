CPPFLAGS=-std=c++11 -pthread -g
LDFLAGS=-g

spydr: spydr.o schedule.o
	g++ $(CPPFLAGS) -o spydr spydr.o schedule.o

spydr.o: spydr.cpp schedule.o json.h
	g++ $(CPPFLAGS) -c spydr.cpp

schedule.o: schedule.cpp program.h schedule.h
	g++ $(CPPFLAGS) -c schedule.cpp

ttest: threadTest.o
	g++ $(CPPFLAGS) -o ttest threadTest.o

threadTest.o: threadTest.cpp schedule.cpp
	g++ $(CPPFLAGS) -c threadTest.cpp schedule.cpp program.h schedule.h -o threadTest.o

jtest: jsonparser.o
	g++ $(CPPFLAGS) -o jtest jsonparser.o

json.o: jsonparser.cpp
	g++ $(CPPFLAGS) -c jsonparser.cpp

clean:
	rm -f *.o spydr ttest jtest
