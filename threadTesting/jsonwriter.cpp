#include "program.h"
#include "schedule.h"
#include "include/rapidjson/document.h"
#include <cstdio>
#include <vector>
#include "include/rapidjson/filereadstream.h"

using namespace rapidjson;

//creates dummy schedule data for testing
vector<Schedule> createSchedules() {

	vector<Schedule> result;
	//lets create 4 schedules just for fun
	for(int i = 0; i < 4; i++) {
		Schedule s;
		//set variables to be dependant on i so they are all different
		s.hour = i+1;
		s.min = i*10;
		//each schedule will have 2 days, the ith day and the (i + 2)th day
		string real_days[] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};
		vector<string> set_days;
		set_days.push_back(real_days[i]);
		set_days.push_back(real_days[i+2]);
		//creating 4 program names. these will actually run.
		//useing actual names of scripts in scripts/ directory
		vector<Program> programs;
		for(int j = 1; j < 5; j++) {
			Program p;
			p.name = "testScript" + to_string(j) + ".sh";
			//initialize the dependencies vector
			vector<Program*> dependencies;
			p.dependencies = dependencies;
			//just dummy values
			p.estMemUsage = (j* (i+1) )*100;
			p.estTime = j * 5;
			p.path = "scripts/" + p.name;
			p.cmdLine = "./" + p.path;
			programs.push_back(p);
		}
		//set different dependencies
		//program[0] will be dependant on program[3] when i == 0
		//program[1] will be dependant on program[2] when i == 1
		//program[2] will be dependant on program[1] when i == 2
		//program[3] will be dependant on program[0] when i == 3
		programs[i].dependencies.push_back(&s.programs[3-i]);
		s.programs = programs;
		//add schedule to list
		result.push_back(s);
	}
	return result;

}

//TODO Write this function!
void writeJson(vector<Schedule> Schedules) {
	//Write me!
}

int main()
{
	vector<Schedule> Schedules = createSchedules();

	writeJson(Schedules);

	return 0;
}
