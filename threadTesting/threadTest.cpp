#include <iostream>
#include <thread>
#include <vector>
#include <stdlib.h>
#include "program.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <dirent.h>
#include <fstream>
#include "schedule.h"

using namespace std;

//string name;
//vector<Program*> dependencies;
//double estMemUsage;
//double estTime;
//string path;
//bool completed = false;

vector<Program> scripts;

void get_scripts() {

	for(int i = 1; i < 5; i++) {
		Program p;
		p.name = "testScript"+to_string(i)+".sh";
		p.estMemUsage = 0;
		p.estTime = 0;
		p.path = "scripts/testScript"+to_string(i)+".sh";
		p.cmdLine = "./"+p.path;
		scripts.push_back(p);
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

void call_from_thread(int x) {

/*
	pid_t pid;
	pid = fork();
	if(pid == 0) {
		cout << "Child #" << getpid() << endl;
		execl(scripts[x].path.c_str(), ( "./"+scripts[x].path ).c_str() );
		//system( ( "./"+scripts[x].path ).c_str() );
	}
*/
//	pid_t id = gettid();
//	cout << "thread #" << x << ": " << id << endl;
//	execl(scripts[x].path.c_str(), ( "./"+scripts[x].path ).c_str() );

	system( ( "./"+scripts[x].path ).c_str() );
	//FILE *fp = popen(scripts[x].c_str(), "r");
}

void track_process(int x) {
	sleep(1);
	cout << "pid: " << getPID(scripts[x].name) << endl;
}

int main() {
	get_scripts();

	vector<thread> th;

//	cout << "main: " << getpid() << endl;

	for(int i = 0; i < scripts.size(); i++) {
		th.push_back(thread(call_from_thread, i));
		th.push_back(thread(track_process, i));
	}

	for(auto &t : th) {
		t.join();
	}
	return 0;
}
