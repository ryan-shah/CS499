/*

This file holds the writeJson and readjson functions.

If changes are made to the json structure's that the website reads/writes, then these functions will need to
	be updated to respond to that

This program will read in a json with a strucure like ../example.json and write out in the form of ../example2.json

These functions are called from spydr.cpp

*/

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
        if (!of.good()) throw ("Can't write the JSON string to the file!");

}

//given a json file, reads the results into a vector of schedules
vector<Schedule> readJson(string filename)
{
	//vector to return
	vector<Schedule> ss;
	//create programs and schedules outside of for loops to prevent pointer errors due to local memory deletion
	Schedule s;
	Program p;
	//index to calculate what schedule we're on
	int s_index = 0;

	// open JSON file
	FILE* fp = fopen(filename.c_str(), "r");   // non-Windows use "r", Windows use "rb"
	if (fp == NULL)
	{
		perror("Failed: ");
		return ss;
	}
	//read in json file
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	//create rapidJson structure
	Document d;
	// parse the JSON file
	d.ParseStream(is);
	// iterate through the parsed JSON file and retrieve the program information
	// for each schedule ...
	for (Value::ConstMemberIterator itr = d["schedules"].MemberBegin();
    	    itr != d["schedules"].MemberEnd(); ++itr)
	{
	    //pull out schedule information
	    s.hour = d["schedules"][itr->name.GetString()]["hour"].GetInt();
	    s.min = d["schedules"][itr->name.GetString()]["min"].GetInt();
	    //get all days
	    for (Value::ConstMemberIterator itr3 = d["schedules"][itr->name.GetString()]["days"].MemberBegin();
		itr3 != d["schedules"][itr->name.GetString()]["days"].MemberEnd(); ++itr3) {
		s.days.push_back(d["schedules"][itr->name.GetString()]["days"][itr3->name.GetString()].GetString());
	    }
	    //get all programs
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
	    //add schedule to list of schedules
	    ss.push_back(s);
	    //read in dependencies
	    for (Value::ConstMemberIterator itr4 = d["schedules"][itr->name.GetString()]["dependencies"].MemberBegin();
		itr4 != d["schedules"][itr->name.GetString()]["dependencies"].MemberEnd(); ++itr4) {
		//get parent and child id's
		int p_id = d["schedules"][itr->name.GetString()]["dependencies"][itr4->name.GetString()]["parent"].GetInt();
		int c_id = d["schedules"][itr->name.GetString()]["dependencies"][itr4->name.GetString()]["child"].GetInt();
		//find parent by id (pointer points to ss[s_index].programs instead of s.programs to prevent memory errors/pointer problems)
		Program* parent;
		for( int i = 0; i < s.programs.size(); i++) {
			if(s.programs[i].id == p_id) {
				parent = &ss[s_index].programs[i];
				break;
			}
		}
		//find child and set parent to point to those programs
		for( int i = 0; i < s.programs.size(); i++) {
			if(s.programs[i].id == c_id) {
				parent->dependencies.push_back(&ss[s_index].programs[i]);
			}
		}
	    }
	    //s_index tracks what shcedule we're dealing with. increment it for next schedule
	    s_index++;
	    //reset vectors in s & p
	    s.programs.clear();
            s.days.clear();
	    p.dependencies.clear();
	}
	fclose(fp);
	return ss;
}
