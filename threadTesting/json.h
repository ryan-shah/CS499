#include "program.h"
#include "schedule.h"
#include "include/rapidjson/document.h"
#include <cstdio>
#include <vector>
#include <fstream>
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/filewritestream.h"
#include "include/rapidjson/prettywriter.h"
#include "include/rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

//given a schedule, creates a json file in the format shown in ../example.json
//printing out to stdout would be nice too for debugging purposes
void writeJson(Schedule Sched, string outfile) {
        //Code goes here
        StringBuffer s;
        PrettyWriter<StringBuffer> writer(s);   // prints in readable JSON format
        writer.StartObject();
        // create an object for each schedule
        writer.Key("programs");
        writer.StartArray();
        // create an object for each program
        for (unsigned j = 0; j < Sched.programs.size(); j++) {
                writer.StartObject();
                writer.Key("id");
                writer.Uint(Sched.programs[j].id);
                writer.Key("name");
                writer.String(Sched.programs[j].name.c_str());
                writer.Key("estMemUsage");
                writer.Uint(Sched.programs[j].estMemUsage);
                writer.Key("estTime");
                writer.Uint(Sched.programs[j].estTime);
                writer.Key("path");
                writer.String(Sched.programs[j].path.c_str());
                writer.Key("cmdLine");
                writer.String(Sched.programs[j].cmdLine.c_str());
                writer.EndObject();
        }
        writer.EndArray();
        writer.EndObject();
        // print the JSON (for testing)
//        cout << s.GetString() << endl;

        // write a JSON file
        string json (s.GetString(), s.GetSize());

        ofstream of (outfile);
        of << json;
        if (!of.good()) throw runtime_error ("Can't write the JSON string to the file!");

}

//given a json file, reads the results into a vector of schedules
vector<Schedule> readJson(string filename)
{
	vector<Schedule> ss;
	Schedule s;
	Program p;
	int s_index = 0;
	// open JSON file
	FILE* fp = fopen(filename.c_str(), "r");   // non-Windows use "r", Windows use "rb"
	if (fp == NULL)
	{
		perror("Failed: ");
		return ss;
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
	    s.hour = d["schedules"][itr->name.GetString()]["hour"].GetInt();
	    s.min = d["schedules"][itr->name.GetString()]["min"].GetInt();
	    for (Value::ConstMemberIterator itr3 = d["schedules"][itr->name.GetString()]["days"].MemberBegin();
		itr3 != d["schedules"][itr->name.GetString()]["days"].MemberEnd(); ++itr3) {
		s.days.push_back(d["schedules"][itr->name.GetString()]["days"][itr3->name.GetString()].GetString());
	    }
	    for (Value::ConstMemberIterator itr2 = d["schedules"][itr->name.GetString()]["programs"].MemberBegin();
		itr2 != d["schedules"][itr->name.GetString()]["programs"].MemberEnd(); ++itr2)
	    {
		p.id = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["id"].GetInt();
                p.name = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["name"].GetString();
                p.estMemUsage = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estMemUsage"].GetDouble();
                p.estTime = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estTime"].GetDouble();
                p.path = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["path"].GetString();
                p.cmdLine = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["cmdLine"].GetString();
                s.programs.push_back(p);   // add the program information to the vector of programs
	    }
	    ss.push_back(s);
	    for (Value::ConstMemberIterator itr4 = d["schedules"][itr->name.GetString()]["dependencies"].MemberBegin();
		itr4 != d["schedules"][itr->name.GetString()]["dependencies"].MemberEnd(); ++itr4) {
		int p_id = d["schedules"][itr->name.GetString()]["dependencies"][itr4->name.GetString()]["parent"].GetInt();
		int c_id = d["schedules"][itr->name.GetString()]["dependencies"][itr4->name.GetString()]["child"].GetInt();
		Program* parent;
		for( int i = 0; i < s.programs.size(); i++) {
			if(s.programs[i].id == p_id) {
				parent = &ss[s_index].programs[i];
				break;
			}
		}
		for( int i = 0; i < s.programs.size(); i++) {
			if(s.programs[i].id == c_id) {
				parent->dependencies.push_back(&ss[s_index].programs[i]);
			}
		}
	    }
	    s_index++;
	    s.programs.clear();
            s.days.clear();
	    p.dependencies.clear();
	}
	fclose(fp);
	return ss;
}
