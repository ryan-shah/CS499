#include "program.h"
#include "schedule.h"
#include "include/rapidjson/document.h"
#include <cstdio>
#include <vector>
#include "include/rapidjson/filereadstream.h"

using namespace rapidjson;
using namespace std;

Schedule readJson(string filename)
{
	Program p;
	Schedule s;
	// open JSON file
	FILE* fp = fopen(filename.c_str(), "r");   // non-Windows use "r", Windows use "rb"
	if (fp == NULL)
	{
		perror("Failed: ");
		return s;
	}
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document d;
	// parse the JSON file
	d.ParseStream(is);
	// iterate through the parsed JSON file and retrieve the program information
	for (Value::ConstMemberIterator itr = d["schedules"].MemberBegin();
    	    itr != d["schedules"].MemberEnd(); ++itr)
	{
//    	    printf("Value of member %s is \n",
//            itr->name.GetString());
	    s.hour = d["schedules"][itr->name.GetString()]["hour"].GetInt();
	    s.min = d["schedules"][itr->name.GetString()]["min"].GetInt();
	    for (Value::ConstMemberIterator itr3 = d["schedules"][itr->name.GetString()]["days"].MemberBegin();
		itr3 != d["schedules"][itr->name.GetString()]["days"].MemberEnd(); ++itr3) {
//		cout << (d["schedules"][itr->name.GetString()]["days"][itr3->name.GetString()].GetString()) << endl;;
		s.days.push_back(d["schedules"][itr->name.GetString()]["days"][itr3->name.GetString()].GetString());
	    }
	    for (Value::ConstMemberIterator itr2 = d["schedules"][itr->name.GetString()]["programs"].MemberBegin();
		itr2 != d["schedules"][itr->name.GetString()]["programs"].MemberEnd(); ++itr2)
	    {
/*		printf("Program name = %s \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["name"].GetString());
		printf("Est. MemUsage = %f \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estMemUsage"].GetDouble());
		printf("Est. Time = %f \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estTime"].GetDouble());
		printf("Path = %s \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["path"].GetString());
		printf("Cmd Line = %s \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["cmdLine"].GetString());
*/
		p.id = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["id"].GetInt();
                p.name = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["name"].GetString();
                p.estMemUsage = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estMemUsage"].GetDouble();
                p.estTime = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estTime"].GetDouble();
                p.path = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["path"].GetString();
                p.cmdLine = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["cmdLine"].GetString();
                s.programs.push_back(p);   // add the program information to the vector of programs
	    }
	    for (Value::ConstMemberIterator itr4 = d["schedules"][itr->name.GetString()]["dependencies"].MemberBegin();
		itr4 != d["schedules"][itr->name.GetString()]["dependencies"].MemberEnd(); ++itr4) {
		int p_id = d["schedules"][itr->name.GetString()]["dependencies"][itr4->name.GetString()]["parent"].GetInt();
		int c_id = d["schedules"][itr->name.GetString()]["dependencies"][itr4->name.GetString()]["child"].GetInt();
		Program* parent;
		for( int i = 0; i < s.programs.size(); i++) {
			if(s.programs[i].id == p_id) {
				parent = &s.programs[i];
				break;
			}
		}
		for( int i = 0; i < s.programs.size(); i++) {
			if(s.programs[i].id == c_id) {
				parent->dependencies.push_back(&s.programs[i]);
			}
		}
	    }
	}
	fclose(fp);
	return s;
}

/*
int main() {
	readJson("../example.json");
}

*/
