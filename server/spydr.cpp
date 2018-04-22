#include "program.h"
#include "schedule.h"
#include "unistd.h"
#include "json.h"
#include "config.h"
#include <thread>

using namespace std;

//used to tell website to read output json
void ping_website() {
	string cmd = string("wget ") + WEBSITE_READ_OUTPUT;
	system(cmd.c_str());
}

//called in thread to run a schedule and write to json & call website's read function
void run_schedule(Schedule* s, string file) {
	s->run();
	try{
		writeJson(*s, file);
		ping_website();
	} catch (...) {
		cout << "could not write to file" << endl;
	}
	if(s->timeToRun()) {
		cout << "finished in < 10 mins, waiting for another 10 to avoid running twice" << endl;
		sleep(2 * RUN_WAIT_TIME);
	}
}

//input -in input.json -out ouput.json
int main(int argc, char *argv[]) {
	if( argc > 5) {
		cout << "usage: " << argv[0] << " -in </path/to/input.json> -out </path/to/output.json>" << endl;
		return 1;
	}
	string infile = INPUT_FILE_DEFAULT;
	string outfile = OUTPUT_FILE_DEFAULT;

	for(int i = 0; i < argc - 1; i++) {
		if(string(argv[i]) == "-in") {
			infile = argv[i+1];
		}
		if(string(argv[i]) == "-out") {
			outfile = argv[i+1];
		}
	}

	while(1) {
		vector<thread> th;
		vector<Schedule> ss;
		try {
			ss = readJson(infile);
		} catch (...) {
			cout << "unable to read json: " << infile << endl;
			return 1;
		}
		for(int i = 0; i < ss.size(); i++) {
			if(ss[i].timeToRun()) {
				cout << "time to run" << endl;
				th.push_back(thread(run_schedule, &ss[i], outfile));
			}
		}
		if(th.size() > 0) {
			for(auto &t : th) {
				t.join();
			}
		} else {
			sleep(RUN_WAIT_TIME);
		}
	}

}

