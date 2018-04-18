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

//given a list of schedules, creates a json file in the format shown in ../example.json
//printing out to stdout would be nice too for debugging purposes
void writeJson(vector<Schedule> Schedules, string outfile) {
        //Code goes here
        StringBuffer s;
        PrettyWriter<StringBuffer> writer(s);   // prints in readable JSON format
        writer.StartObject();
        // create an object for each schedule
        for (unsigned i = 0; i < Schedules.size(); i++) {
                writer.Key("programs");
                writer.StartArray();
                // create an object for each program
                for (unsigned j = 0; j < Schedules[i].programs.size(); j++) {
                        writer.StartObject();
                        writer.Key("id");
                        writer.Uint(Schedules[i].programs[j].id);
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
                writer.EndArray();
        }
        writer.EndObject();
        // print the JSON (for testing)
//        cout << s.GetString() << endl;

        // write a JSON file
        string json (s.GetString(), s.GetSize());

        ofstream of (outfile);
        of << json;
        if (!of.good()) throw runtime_error ("Can't write the JSON string to the file!");

}

vector<Schedule> readJson(string filename)
{
	vector<Schedule> ss;
	Schedule s;
	Program p;
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
	    ss.push_back(s);
	    s.programs.clear();
            s.days.clear();
	    p.dependencies.clear();
	}
	fclose(fp);
	return ss;
}
/*
int main() {
	vector<Schedule> test = readJson("testJson.json");
	for(int i = 0; i < test.size(); i++) {
		cout << "hour: " << test[i].hour << endl;
		cout << "min: " << test[i].min << endl;
		cout << "days: ";
		for(int j = 0; j < test[i].days.size(); j++) {
			cout << test[i].days[j] << ", ";
		}
		cout << endl;
		for(int j = 0; j < test[i].programs.size(); j++) {
			Program p = test[i].programs[j];
			cout << "\tname: " << p.name << endl;
			cout << "\tid: " << p.id << endl;
			cout << "\testMemUsage: " << p.estMemUsage << endl;
			cout << "\testTime: " << p.estTime << endl;
			cout << "\tpath: " << p.path << endl;
			cout << "\tcmdLine: " << p.cmdLine << endl;
			for(int k = 0; k < p.dependencies.size(); k++) {
				cout << "\t\tid: " << p.dependencies[k]->id << endl;
			}
		}
	}
}
*/
