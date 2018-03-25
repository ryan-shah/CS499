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
				statFile.close();
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

void track_process(Program *P) {
	sleep(1);
	int pid = getPID(P->name);
	time_t start = time(NULL);
	long int maxMem = 0;
	while(pid != -1) {
		string pidPath = "/proc/"+to_string(pid)+"/stat";

		//open /proc/PID/stat
		ifstream stat_file( pidPath.c_str() );
		string line_buff;
		getline(stat_file, line_buff);
		stat_file.close();
		vector<string> parts = split(line_buff);
		string mem = parts[22];
		long int memVal = atoi(mem);
		if(memVal > maxMem) {
			maxMem = memVal;
		}

		pid = getPID(P->name);
	}
	time_t end = time(NULL);
	double time_diff = difftime(start, end);
	cout << time_diff << endl;
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
