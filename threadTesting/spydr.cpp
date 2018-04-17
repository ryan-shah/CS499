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

int main() {

	while(1) {
		vector<thread> th;
		vector<Schedule> ss = readJson("testJson.json");
		for(int i = 0; i < ss.size(); i++) {
			if(ss[i].timeToRun()) {
				cout << "time to run" << endl;
				ss[i].run();
				if(ss[i].timeToRun()) {
					cout << "extra sleepy" << endl;
					sleep(10*60);
				}
//				th.push_back(thread(run_schedule, &ss[i]));
			}
		}
		/*
		if(th.size() > 0) {
			for(auto &t : th) {
				t.join();
			}
			th.clear();
		}
		*/
	}

}

