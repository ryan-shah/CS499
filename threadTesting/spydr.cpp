#include "program.h"
#include "schedule.h"
#include "unistd.h"
#include "json.h"
#include <thread>

using namespace std;

void run_schedule(Schedule* s) {
	s->run();
	if(s->timeToRun()) {
		cout << "finished in < 10 mins, waiting for another 10 to avoid running twice" << endl;
		sleep(10*60);
	}
}

//input -in input.json -out ouput.json
int main(int argc, char *argv[]) {
	if( argc != 5) {
		cout << "usage: " << argv[0] << " -in </path/to/input.json> -out </path/to/output.json>" << endl;
		return 1;
	}
	string infile = "";
	string outfile = "";

	for(int i = 0; i < 4; i++) {
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
				th.push_back(thread(run_schedule, &ss[i]));
			}
		}
		if(th.size() > 0) {
			for(auto &t : th) {
				t.join();
			}
			try {
				writeJson(ss, outfile);
			} catch (...) {
				cout << "unable to write to file: " << outfile << endl;
				return 1;
			}
		} else {
			sleep(5*60);
		}
	}

}

