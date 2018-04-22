#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <iostream>
#include <vector>
#include "program.h"

using namespace std;

class Schedule {
public:
	int hour;
	int min;
	//list of days to run (monday, tuesday, wednesday, ...)
	vector<string> days;

	vector<Program> programs;

	//load programs from file
	void get_scripts();
	//run the schedule
	void run();
	//check to see if it is time to run
	bool timeToRun();
};

#endif
