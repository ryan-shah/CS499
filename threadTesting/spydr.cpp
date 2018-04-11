#include "program.h"
#include "schedule.h"

using namespace std;

int main() {

	Schedule s;
	s.get_scripts();
	s.hour = 13;
	s.min = 19;
	s.days.push_back("wednesday");

	s.programs[0].dependencies.push_back(&s.programs[1]);

	if(s.timeToRun()) {
		cout << "time to run" << endl;
		s.run();
	}

}
