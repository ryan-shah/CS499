#include "program.h"
#include "schedule.h"
#include "unistd.h"
using namespace std;

int main() {

while(1) {

	Schedule s;
	s.get_scripts();
	s.hour = 11;
	s.min = 20;
	s.days.push_back("wednesday");

	s.programs[0].dependencies.push_back(&s.programs[1]);

	if(s.timeToRun()) {
		cout << "time to run" << endl;
		s.run();
		if(s.timeToRun() ) {
			cout << "finished in < 10 mins, waiting for another 10 to avoid running twice" << endl;
			sleep(10*60);
		}

	} else {
		sleep(5 * 60);
	}

}

}
