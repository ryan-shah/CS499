#include <iostream>
#include <thread>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <dirent.h>
#include <fstream>
#include <queue>
#include <ctime>
#include <cmath>
#include "program.h"
#include "schedule.h"

using namespace std;

//given a name of a program searches through /proc/PID/cmdline files to find
//a process with the same name
//returns PID if successfull else -1
int getPID(string name) {
	int pid = -1;
	//open /proc dir
	DIR *dp = opendir("/proc");

	if( dp != NULL ) {

		struct dirent *dirp;
		//go through each directory
		while ( pid < 0 && (dirp = readdir(dp)) ) {
			int id = atoi(dirp->d_name);

			if(id > 0) {
				//found a directory with a PID
				string cmdPath = string("/proc/") + dirp->d_name + "/cmdline";
				//open /proc/PID/cmdline and read line
				ifstream cmdFile(cmdPath.c_str());
				string cmdLine;
				getline(cmdFile, cmdLine);
				cmdFile.close();

				//line format is the command lline
				//see if line contains the name of the script were searching for
				if(cmdLine.find(name) != string::npos && cmdLine.find("sh") != 0) {
					pid = id;
					break;
				}
			}
		}
	}
	closedir(dp);
	return pid;
}

//helper function that runs a given program using system
void call_from_thread(Program *P) {
	cout << "running program: " << P->name << endl;
	int status = system( P->cmdLine.c_str() );
	P->returnVal = status;
	P->completed = true;
}

//helper function that takes a string and splits it on " " and returns a vector of the peices
vector<string> split(string x) {
	string buff;
	vector<string> result;
	size_t pos = x.find(" ");
	while(pos != string::npos) {
		buff = x.substr(0, pos);
		x = x.substr(pos+1, string::npos);
		result.push_back(buff);
		pos = x.find(" ");
	}
	return result;
}

//tracks the process to record memory usage
//given a program* finds the program name then opens /proc/PID/stat and records information on it
void track_process(Program *P) {
	//wait 1 sec to avoid concurrence errors
	sleep(1);
	//find the pid
	int pid = getPID(P->name);
	cout << "Tracking process " << P->name << " with PID: " << pid << endl;
	time_t start = time(NULL);
	long int maxMem = 0;
	while(pid != -1) {
		string pidPath = "/proc/"+to_string(pid)+"/stat";

		//open /proc/PID/stat
		ifstream stat_file( pidPath.c_str() );
		string line_buff;
		//get line
		getline(stat_file, line_buff);
		stat_file.close();
		//split the line into its parts
		vector<string> parts = split(line_buff);
		//memory is the 22nd entry
		string mem = parts[22];
		long int memVal = stol(mem);
		if(memVal > maxMem) {
			maxMem = memVal;
		}

		pid = getPID(P->name);
	}
	time_t end = time(NULL);
	//calculate run time
	double time_diff = difftime(end, start);
	cout << "Program " << P->name << " finished in "<< time_diff << " seconds." << endl;
	cout << "Program " << P->name << " used "<< maxMem << " bytes of memory." << endl;
	cout << maxMem << endl;

	P->estMemUsage = maxMem;
	P->estTime = time_diff+1;
}

//helper function to see if a vector contains an element
bool contains(vector<string> list, string el) {
	for(int i = 0; i < list.size(); i++) {
		string x = list[i];
		for(int j = 0; j < x.length(); j++) {
			x[j] = tolower(x[j]);
		}
		if(x == el) {
			return true;
		}
	}
	return false;
}

//helper function that determines if it is time to run the program
bool Schedule::timeToRun() {
	cout << "checking time... " << endl;
	time_t now = time(NULL);
	//get local time
	struct tm nowTM = *localtime(&now);
	//check to see if the current weekday is in the vector of days to run on
	switch( nowTM.tm_wday ) {
		case 0:
			if(!contains(days, "sunday")) return false;
			break;
		case 1:
			if(!contains(days, "monday")) return false;
			break;
		case 2:
			if(!contains(days, "tuesday")) return false;
			break;
		case 3:
			if(!contains(days, "wednesday")) return false;
			break;
		case 4:
			if(!contains(days, "thursday")) return false;
			break;
		case 5:
			if(!contains(days, "friday")) return false;
			break;
		case 6:
			if(!contains(days, "saturday")) return false;
			break;
		default:
			return false;
	}
	//set time from schedule class to a tm struct
	struct tm startTime = *localtime(&now);
	startTime.tm_hour = hour;
	startTime.tm_min = min;
	//check to see how close the two times are
	double diff = difftime(now, mktime(&startTime) );
	//return true if within 5 mins of execution time
	if( abs(diff / 60) < 5 ) {
		return true;
	}
	return false;
}

//runs a schedule
void Schedule::run() {
	vector<thread> th;
	vector<Program*> toRun;
	queue<Program*> canRun;

	//reset dependencies
	/*
	for(int i = 0; i < programs.size(); i++) {
		for(int j = 0; j < programs[i].dependencies.size(); j++) {
			for(int k = 0; k < programs.size(); k++) {
				if(programs[i].dependencies[j]->id == programs[k].id) {
					programs[i].dependencies[j] = &programs[k];
					break;
				}
			}
		}
	}
	*/

	//make pointers for toRun of all programs in schedule
	for(int i = 0; i < programs.size(); i++) {
		toRun.push_back(&programs[i]);
	}

	//cycle through toRun until its empty
	while(toRun.size() > 0) {
		for(int i = 0; i < toRun.size(); i++) {
			//if program can be run remove from toRun and add to canRun
			if( toRun[i]->canRun() ) {
				canRun.push( toRun[i] );
				toRun.erase( toRun.begin()+i );
				break;
			}
		}
		//if there are programs to run pop one off and run it if you can
		if( !canRun.empty() ) {
			Program *p = canRun.front();
			canRun.pop();
			if( p->checkMem() ) {
				th.push_back(thread(call_from_thread, p) );
				th.push_back(thread(track_process, p) );
			} else {
				canRun.push(p);
			}
		}
	}
	//all programs are able to run, keep popping elements and running them if able
	//this will run forever if unable to start a process due to memory constraints
	while( !canRun.empty() ) {

		Program *p = canRun.front();
		canRun.pop();
		if( p->checkMem() ) {
			th.push_back(thread(call_from_thread, p) );
			th.push_back(thread(track_process, p) );
		} else {
			canRun.push(p);
		}

	}

	//wait for all threads to finish
	for(auto &t : th) {
		t.join();
	}
	return;
}
