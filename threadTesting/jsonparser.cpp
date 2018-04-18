#include "program.h"
#include "schedule.h"
#include "include/rapidjson/document.h"
#include <cstdio>
#include <string>
#include<iostream>
#include <vector>
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

int main()
{
	Program p;
	Schedule s;
	int ctr;
	// open JSON file
	FILE* fp = fopen("../example.json", "r");   // non-Windows use "r", Windows use "rb"
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
	for (Value::ConstMemberIterator itr = d["schedules"].MemberBegin();
    	    itr != d["schedules"].MemberEnd(); ++itr)
	{
    	    printf("Value of member %s is \n",
            itr->name.GetString());
	    printf("hour: %i \n", d["schedules"][itr->name.GetString()]["hour"].GetInt());
	    s.hour = d["schedules"][itr->name.GetString()]["hour"].GetInt();
	    s.min = d["schedules"][itr->name.GetString()]["min"].GetInt();
	    ctr = 0;
	    for (Value::ConstValueIterator itr2 = d["schedules"][itr->name.GetString()]["days"].Begin();
                itr2 != d["schedules"][itr->name.GetString()]["days"].End(); ++itr2)
	    {
		s.days.push_back(d["schedules"][itr->name.GetString()]["days"][ctr].GetString());
		ctr++;	
	    }
	    for (Value::ConstMemberIterator itr2 = d["schedules"][itr->name.GetString()]["programs"].MemberBegin();
		itr2 != d["schedules"][itr->name.GetString()]["programs"].MemberEnd(); ++itr2)
	    {
		printf("Program name = %s \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["name"].GetString());
		printf("Est. MemUsage = %f \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estMemUsage"].GetDouble());
		printf("Est. Time = %f \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estTime"].GetDouble());
		printf("Path = %s \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["path"].GetString());
		printf("Cmd Line = %s \n", d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["cmdLine"].GetString());

		p.id = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["id"].GetInt();
                p.name = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["name"].GetString();
                p.estMemUsage = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estMemUsage"].GetDouble();
                p.estTime = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["estTime"].GetDouble();
                p.path = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["path"].GetString();
                p.cmdLine = d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["cmdLine"].GetString();
                s.programs.push_back(p);   // add the program information to the vector of programs
	    }
	    for (Value::ConstMemberIterator itr2 = d["schedules"][itr->name.GetString()]["dependencies"].MemberBegin();
                itr2 != d["schedules"][itr->name.GetString()]["dependencies"].MemberEnd(); ++itr2)
	    {
		
		p.dependencies.push_back(*d["schedules"][itr->name.GetString()]["programs"][itr2->name.GetString()]["name"].GetString());
	    }
	}
	for (int i = 0; i < s.days.size(); i++)
	{
		cout << s.days[i] << endl;
	}
	// Stringify the DOM
    	StringBuffer buffer;
	PrettyWriter<StringBuffer> writer(buffer);   // prints in readable JSON format
    	//Writer<StringBuffer> writer(buffer);
    	d.Accept(writer);
	cout << buffer.GetString() << endl;
	fclose(fp);
	return 0;
}
