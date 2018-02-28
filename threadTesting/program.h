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
	int estMemUsage;
	bool completed = false;

	//functions
	bool canRun() {
		for(int i = 0; i < dependencies.size(); i++) {
			if(dependencies[i]->completed == false) {
				return false;
			}
		}
		return true;
	}
};

#endif
