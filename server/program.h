#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <vector>

using namespace std;

class Program {

public:
	//variables
	int id;
	string name;
	vector<Program*> dependencies;
	double estMemUsage;
	double estTime;
	string path;
	bool completed = false;
	string cmdLine;
	int returnVal;

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
		if(availMem > estMemUsage) {
			return true;
		} else {
			return false;
		}
	}
};

#endif
