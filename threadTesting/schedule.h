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

	vector<string> days;

	vector<Program> programs;

	void get_scripts();
	void run();
	bool timeToRun();
};

#endif
