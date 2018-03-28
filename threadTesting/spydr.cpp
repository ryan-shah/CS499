#include "program.h"
#include "schedule.h"

using namespace std;

int main() {

	Schedule s;
	s.get_scripts();
	s.hour = 11;
	s.min = 30;
	s.days.push_back("wednesday");

	if(s.timeToRun()) {
		cout << "time to run" << endl;
		s.run();
	}

}
