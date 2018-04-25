
/*

This is the class structure for Program
Only two fucntions are called relating to a program, canRun and checkMem

This class is referenced by Schedule.h

*/

#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <vector>

using namespace std;

class Program {

public:
	//variables
	//program id
	int id;
	//program name
	string name;
	//list of dependencies
	vector<Program*> dependencies;
	//estimated memory and time. Updated when schedule is run
	long int estMemUsage;
	double estTime;
	//path to file
	string path;
	//bool telling if program has completed
	bool completed = false;
	//the command line needed to execute the script
	string cmdLine;
	//the return value of the program. Not used, but if error checking of programs needs to be checked in the
	//future this will be relavent. This value is set when program is finished running but its value is not checked for success
	int returnVal;
	//TODO: this will eventually be used to track cluster processes. If this is set to true, then instead of
	//track_process, track_cluster must be called
	bool isCluster = false;

	//functions
	//returns true if all dependencies have been completed
	bool canRun() {
		for(int i = 0; i < dependencies.size(); i++) {
			if(dependencies[i]->completed == false) {
				return false;
			}
		}
		return true;
	}

	//opens files from /proc/ to check if there is enough memory to execute a given program
	bool checkMem() {
		//get available memory
		//open /proc/meminfo ( format listed in man proc )
		FILE *mem_file = fopen( "/proc/meminfo", "r" );
		long int totalMem = 0;
		//scan first line to get total memory
		fscanf(mem_file, "%*s %lu %*s", &totalMem);
		//mem vals are in kB
		long int availMem = 0;
		//scan next 2 lines and get available memory from line 3
		fscanf(mem_file, "%*s %*u %*s %*s %lu %*s", &availMem);
		//if available memory and check to see if it is more than available memory
		if( (availMem * 1000) > estMemUsage) {
			return true;
		} else {
			return false;
		}
	}
};

#endif
