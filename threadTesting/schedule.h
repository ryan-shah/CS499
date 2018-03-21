#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <vector>

using namespace std;

class Schedule {

	int hour;
	int min;

	vector<string> days;

	vector<Program> programs;

	void run();

};

#endif
