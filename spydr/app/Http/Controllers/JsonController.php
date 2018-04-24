<?php

namespace App\Http\Controllers;

use App\Dependency;
use App\Program;
use App\Runlist;
use App\RunlistParameter;
use Illuminate\Support\Facades\File;

class JsonController extends Controller
{

    //When retrieving a hash entry, we need to parse out the value from the hash
    public function parseHash($input){

        //Parse out the definition from the hash values
        return strtok(explode(':', $input)[1], '}');

    }

    //Retrieve a reference schedules and various database entries and add a dependency to the schedules array
    public function addDependency($runlist, &$schedules, $rpid_parsed, $program): void
    {

        //Try to grab a string representation of the did of the dependency
        $did = (string)Dependency::select('did')->find($runlist->program_id);

        //If there is an existing dependency
        if (!empty($did)) {

            //Parse the string until only the did is left
            $did_parsed = $this->parseHash($did);

            //If the Dependency does not already exist in the array
            if (!isset($schedules["schedules"][$rpid_parsed]["dependencies"][$did_parsed])) {

                //Grab the row of the Dependency table associated with the program in question
                $dependency = Dependency::select('did')->find($program->pid);

                //Add the dependency information
                $schedules["schedules"][$rpid_parsed]["dependencies"][$did_parsed]["parent"] = $dependency->program_id;
                $schedules["schedules"][$rpid_parsed]["dependencies"][$did_parsed]["child"] = $dependency->dependency_id;

            }

        }

    }

    //Retrieve a reference schedules and various database entries and add a program to the schedules array
    public function addProgram($runlist, &$schedules, $rpid_parsed, &$program, &$pid_parsed): void{

        //Add the Program information from the database
        $program = Program::find($runlist->program_id);

        //Grab and parse the string so that only the pid is left
        $pid_parsed = $this->parseHash((string)Program::select('pid')->find($runlist->program_id));

        //Insert the program information into the array
        $schedules["schedules"][$rpid_parsed]["programs"][$pid_parsed]["id"] = $program->pid;
        $schedules["schedules"][$rpid_parsed]["programs"][$pid_parsed]["name"] = $program->pname;
        $schedules["schedules"][$rpid_parsed]["programs"][$pid_parsed]["estMemUsage"] = $program->estimated_memory_usage;
        $schedules["schedules"][$rpid_parsed]["programs"][$pid_parsed]["estTime"] = $program->estimated_time;
        $schedules["schedules"][$rpid_parsed]["programs"][$pid_parsed]["path"] = $program->path;
        $schedules["schedules"][$rpid_parsed]["programs"][$pid_parsed]["cmdLine"] = $program->command_line;

    }

    //Creates the text that will be supplied to spydr.json
    public function createJson(){

        //Initialize the arrays we will use to create the resulting JSON
        $schedules = [
            "schedules" => []
        ];

        //Retrieve the entire Runlist table
        $runlists = Runlist::all();

        //Go through each row of the Runlist table
        foreach($runlists as $runlist){

            //Grab a string representation of the runlist row
            $rpid = (string)RunlistParameter::select('rpid')->find($runlist->runlist_id);

            //Grab and parse the string so that only the rpid is left
            $rpid_parsed = $this->parseHash($rpid);

            //If the Runlist Parameter does not already exist in the array
            if(!isset($schedules["schedules"][$rpid_parsed])){

                //Collect the Runlist Parameter information from the database
                $runlist_parameter = RunlistParameter::find($runlist->runlist_id);

                //Parse the rtime information into hour and min for the array
                $schedules["schedules"][$rpid_parsed]["hour"] = date('H', strtotime($runlist_parameter->rtime));
                $schedules["schedules"][$rpid_parsed]["min"] = date('i', strtotime($runlist_parameter->rtime));

                //Add hard-coded days [NEEDS TO BE UPDATED ONCE DAYS ARE IMPLEMENTED TO THE WEBSITE]
                $days = json_decode($runlist_parameter->days);
                $i = 1;
                foreach($days as $day){
                    $schedules["schedules"][$rpid_parsed]["days"]["$i"] = "$day";
                    $i++;
                }

                //Add the program information
                $this->addProgram($runlist, $schedules, $rpid_parsed, $program, $pid);

                //Add the dependency information
                $this->addDependency($runlist, $schedules, $rpid_parsed, $program);

            }

            //If the Runlist Parameter already exists in the array
            else{

                //Add the program information
                $this->addProgram($runlist, $schedules, $rpid_parsed, $program, $pid);

                //Add the dependency information
                $this->addDependency($runlist, $schedules, $rpid_parsed, $program);

            }

            //If there is not an existing dependency
            if(!array_key_exists("dependencies", $schedules["schedules"][$rpid_parsed])) {

                //Add an empty dependency into the JSON
                $schedules["schedules"][$rpid_parsed]["dependencies"] = json_decode("{}");

            }

        }

        //Return the encoded version of the array
        return json_encode($schedules);

    }

    //Replace the older version of spydr.json with a new one
    //Called after any update to the database is made
    public function updateJson(){

        //Delete spydr.json if it exists, as well as make sure it is deleted afterwards,
        //since File::delete() does not check for deletion
        $filename = storage_path("../../server/spydr.json");
        while (File::exists($filename)){
            File::delete($filename);
        }

        //Create the content of spydr.json
        $spydr = $this->createJson();

        //Replace the previous spydr.json with the updated version
        File::put($filename, $spydr);

    }

}