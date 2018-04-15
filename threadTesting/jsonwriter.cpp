#include "program.h"
#include "schedule.h"
#include "include/rapidjson/document.h"
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/filewritestream.h"
#include "include/rapidjson/prettywriter.h"
#include "include/rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

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
//given a list of schedules, creates a json file in the format shown in ../example.json
//printing out to stdout would be nice too for debugging purposes
void writeJson(vector<Schedule> Schedules) {
	//Code goes here
	
	StringBuffer s;
	PrettyWriter<StringBuffer> writer(s);   // prints in readable JSON format
	writer.StartObject();
	writer.Key("schedules");
	writer.StartObject();
	// create an object for each schedule
	for (unsigned i = 0; i < Schedules.size(); i++) {
		writer.Key(to_string(i).c_str());
		writer.StartObject();
		writer.Key("hour");
		writer.Uint(Schedules[i].hour);
		writer.Key("min");
                writer.Uint(Schedules[i].min);
		writer.Key("programs");
		writer.StartObject();
		// create an object for each program
		for (unsigned j = 0; j < Schedules[i].programs.size(); j++) {
			writer.Key(to_string(j).c_str());
			writer.StartObject();
			writer.Key("name");
			writer.String(Schedules[i].programs[j].name.c_str());
			writer.Key("estMemUsage");
			writer.Uint(Schedules[i].programs[j].estMemUsage);
			writer.Key("estTime");
                        writer.Uint(Schedules[i].programs[j].estTime);
			writer.Key("path");
                        writer.String(Schedules[i].programs[j].path.c_str());
			writer.Key("cmdLine");
                        writer.String(Schedules[i].programs[j].cmdLine.c_str());
			writer.EndObject();
		}
		writer.EndObject();
		writer.Key("dependencies");
		writer.StartObject();
		int ctr = 0;
		// create an object for each dependency
		for (unsigned j = 0; j < Schedules[i].programs.size(); j++) {
			for (unsigned k = 0; k < Schedules[i].programs[j].dependencies.size(); k++) {
				writer.Key(to_string(ctr).c_str());
				ctr++;
				writer.StartObject();
				writer.Key("parent");
				writer.String("Parent");
				writer.Key("child");
				writer.String(Schedules[i].programs[j].name.c_str());
				writer.EndObject();
			}
		}
		writer.EndObject();
			
		writer.EndObject(); 
	}
	writer.EndObject();
	writer.EndObject();
	// print the JSON (for testing)
	cout << s.GetString() << endl;
	
	// write a JSON file
	string json (s.GetString(), s.GetSize());

	ofstream of ("output.json");
	of << json;
	if (!of.good()) throw runtime_error ("Can't write the JSON string to the file!");
	
}

int main()
{
	//create a list of schedules
	vector<Schedule> Schedules = createSchedules();
	//write this to json
	writeJson(Schedules);
	//we done boi
	return 0;
}
