#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <vector>

using namespace std;

class Program {

public:
	//variables
	string name;
	vector<Program*> dependencies;
	double estMemUsage;
	double estTime;
	string path;
	bool completed = false;
	string cmdLine;
	int returnVal;

	//functions
	bool canRun() {
		for(int i = 0; i < dependencies.size(); i++) {
			if(dependencies[i]->completed == false) {
				return false;
			}
		}
		return true;
	}

	bool checkMem() {
		FILE *mem_file = fopen( "/proc/meminfo", "r" );
		long int totalMem = 0;
		fscanf(mem_file, "%*s %lu %*s", &totalMem);
		//mem vals are in kB
		long int availMem = 0;
		fscanf(mem_file, "%*s %*u %*s %*s %lu %*s", &availMem);

		if(availMem > estMemUsage) {
			return true;
		} else {
			return false;
		}
	}
};

#endif
