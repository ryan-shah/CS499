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
		return true;
	}
};

#endif
