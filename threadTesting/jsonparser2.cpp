#include "program.h"
#include "schedule.h"
#include "include/rapidjson/document.h"
#include <cstdio>
#include <vector>
#include "include/rapidjson/filereadstream.h"
#include <fstream>
#include <streambuf>

using namespace rapidjson;
using namespace std;

//view ../example2.json to see structure
int main()
{
	Program p;
	Schedule s;
	// open JSON file
	ifstream json_file("testJson.json");
	//read to string
	string buff( (istreambuf_iterator<char>(json_file)), istreambuf_iterator<char>() );
	//parse json
	Document doc;
	doc.Parse(buff.c_str());
	//iterate through each schedule
	const Value& schedules = doc["schedules"];
	for(auto& v : schedules.GetArray()) {
		cout << "SCHEDULE: {" << endl;
		//do stuff with data
		cout << "\thour: " << v["hour"].GetInt() << endl;
		cout << "\tmin: " << v["min"].GetInt() << endl;
		cout << "\tdays: ";
		for(auto& day : v["days"].GetArray()) {
			cout << day.GetString() << ", ";
		}
		cout << endl;
		cout << "\tprograms: {" << endl;
		for(auto& program : v["programs"].GetArray()) {
			cout << "\t\tProgram: {" << endl;
			cout << "\t\t\tname: " << program["name"].GetString() << endl;
			cout << "\t\t\testMemUsage: " << program["estMemUsage"].GetDouble() << endl;
			cout << "\t\t\testTime: " << program["estTime"].GetDouble() << endl;
			cout << "\t\t\tpath: " << program["path"].GetString() << endl;
			cout << "\t\t\tcmdLine: " << program["cmdLine"].GetString() << endl;
			cout << "\t\t}" << endl;
		}
		cout << "\t}" << endl;

		cout << "\tdependencies: {" << endl;
		for(auto& dependency : v["dependencies"].GetArray()) {
			cout << "\t\t" << dependency["parent"].GetString() << " is dependant on " << dependency["child"].GetString() << endl;
		}
		cout << "\t}" << endl;
		cout << "}" << endl;
	}
/*
	FILE* fp = fopen("testJson.json", "r");   // non-Windows use "r", Windows use "rb"
	if (fp == NULL)
	{
		perror("Failed: ");
		return 1;
	}
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document d;
	// parse the JSON file
	d.ParseStream(is);
	// iterate through the parsed JSON file and retrieve the program information
	for (Value::ConstMemberIterator itr = d["schedules"].MemberBegin(); itr != d["schedules"].MemberEnd(); ++itr)
	{
    	    printf("Value of member %s is \n",
            itr->name.GetString());
	    for (Value::ConstMemberIterator itr2 = d["schedules"][itr->name.GetString()]["programs"].MemberBegin();
		itr2 != d["schedules"][itr->name.GetString()]["programs"].MemberEnd(); ++itr2)
	    {
		printf("Program name = %s \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["name"].GetString());
		printf("Est. MemUsage = %f \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estMemUsage"].GetDouble());
		printf("Est. Time = %f \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estTime"].GetDouble());
		printf("Path = %s \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["path"].GetString());
		printf("Cmd Line = %s \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["cmdLine"].GetString());

                p.name = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["name"].GetString();
                p.estMemUsage = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estMemUsage"].GetDouble();
                p.estTime = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estTime"].GetDouble();
                p.path = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["path"].GetString();
                p.cmdLine = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["cmdLine"].GetString();
                s.programs.push_back(p);   // add the program information to the vector of programs
	    }
	}
	fclose(fp);
*/
	return 0;
}
