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
#include "schedule.h"
#include "program.h"

using namespace std;

//string name;
//vector<Program*> dependencies;
//double estMemUsage;
//double estTime;
//string path;
//bool completed = false;
//string cmdLine
//int returnVal

void get_scripts() {

	for(int i = 1; i < 5; i++) {
		Program p;
		p.name = "testScript"+to_string(i)+".sh";
		p.estMemUsage = 0;
		p.estTime = i * 5;
		p.path = "scripts/testScript"+to_string(i)+".sh";
		p.cmdLine = "./" + path;
		programs.push_back(p);
	}

}

int getPID(string name) {
	int pid = -1;
	DIR *dp = opendir("/proc");

	if( dp != NULL ) {

		struct dirent *dirp;
		while ( pid < 0 && (dirp = readdir(dp)) ) {
			int id = atoi(dirp->d_name);

			if(id > 0) {
				string statPath = string("/proc/") + dirp->d_name + "/stat";
				ifstream statFile(statPath.c_str());
				string statLine;
				getline(statFile, statLine);
				if( !statLine.empty() ) {
					size_t pos = statLine.find('\0');
					if (pos != string::npos)
						statLine = statLine.substr(0, pos);
					pos = statLine.find('(');
					statLine = statLine.substr(pos + 1);
					pos = statLine.find(')');
					statLine = statLine.substr(0, pos);
					if(name == statLine) {
						pid = id;
					}
				}
			}
		}
	}
	closedir(dp);
	return pid;
}

void call_from_thread(Program *P) {
	int status = system( P->cmdLine.c_str() );
	P->returnVal = status;
	P->completed = true;
}

struct pstat {
	long unsigned int utime_ticks;
	long int cutime_ticks;
	long unsigned int stime_ticks;
	long int cstime_ticks;
	long unsigned int vsize; // virtual memory size in bytes
	long unsigned int rss; //Resident  Set  Size in bytes
	long unsigned int cpu_total_time;
}

void track_process(Program *P) {
	sleep(1);
	pstat data;
	int pid = getPID(P->name);
	while(pid != -1) {
		string pidPath = "/proc/"+to_string(pid)+"/stat";

		//open /proc/PID/stat
		FILE *fpstat = fopen(pidPath, "r");
		if(fpstat == NULL) {
			fclose(fpstat);
			break;
		}
		//open /proc/stat
		FILE *fstat = fopen("/proc/stat", "r");
		if(fstat == NULL) {
			perror("FOPEN ERROR");
			fclose(fstat);
			break;
		}

		//read values from proc/pid/stat
		long int rss;
		if( fscanf(fpstat, "%*d %*s %*c %*d %*d% *d %*d %*d %*u %*u %*u %*u %*u %lu %lu %ld %ld %*d %*d %*d %*d %*u %lu %ld", &result.utime_ticks, &result.stime_ticks, &result.cstime_ticks, &result.vsize, &rss) == EOF) {
			fclose(fpstat);
			break;
		}
		fclose(fpstat);
		result.rss = rss * getpagessize();

		//read + calc cpu total time from /proc/stat
		long unsigned int cpu_time[10];
		if( fscanf(fstat, "%*s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu", &cpu_time[0], &cpu_time[1], &cpu_time[2], &cpu_time[3], &cpu_time[4], &cpu_time[5], &cpu_time[6], &cpu_time[7], &cpu_time[8], &cpu_time[9]) == EOF) {
			fclose(fstat);
			break;
		}
		fclose(fstat);

		for(int i = 0; i < 4; i++) {
			result.cpu_total_time += cpu_time[i];
		}
		//

		pid = getPID(P->name);
	}
}

/*
int hour;
int min;
vector<string> days;
vector<Program> programs;
*/
void Schedule::run() {
	get_scripts();

	vector<thread> th;
	vector<Program*> toRun;
	queue<Program*> canRun;

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
			Program *p = canRun.pop();
			if( p->checkMem() ) {
				th.push_back(thread(call_from_thread, p) );
				th.push_back(thread(track_process, p) );
			} else {
				canRun.push(p);
			}
		}
	}

	while( !canRun.empty() ) {

		Program *p = canRun.pop();
		if( p->checkMem() ) {
			th.push_back(thread(call_from_thread, p) );
			th.push_back(thread(track_process, p) );
		} else {
			canRun.push(p);
		}

	}

	for(auto &t : th) {
		t.join();
	}
	return 0;
}
