<?php

namespace App\Http\Controllers;

use App\Dependency;
use App\Program;
use App\Runlist;
use App\RunlistParameter;
use Illuminate\Support\Facades\File;

class JsonController extends Controller
{

    public function parseHash($input){

        //Parse out the definition from the hash element
        return strtok(explode(':', $input)[1], '}');

    }

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

                //Grab the row of the Dependancy table associated with the program in question
                $dependency = Dependency::select('did')->find($program->pid);

                //Add the dependency information
                $schedules["schedules"][$rpid_parsed]["dependencies"][$did_parsed]["parent"] = $dependency->program_id;
                $schedules["schedules"][$rpid_parsed]["dependencies"][$did_parsed]["child"] = $dependency->dependency_id;

            }

        }

        //If there is not an existing dependency
        else {

            //Add an empty dependency into the JSON
            $schedules["schedules"][$rpid_parsed]["dependencies"] = [];

        }

    }

    public function addProgram($runlist, &$schedules, $rpid, &$program, &$pid): void{

        //Add the Program information from the database
        $program = Program::find($runlist->program_id);

        //Grab and parse the string so that only the pid is left
        $pid = $this->parseHash((string)Program::select('pid')->find($runlist->program_id));

        //Insert the program information into the array
        $schedules["schedules"][$rpid]["programs"][$pid]["id"] = $program->pid;
        $schedules["schedules"][$rpid]["programs"][$pid]["name"] = $program->pname;
        $schedules["schedules"][$rpid]["programs"][$pid]["estMemUsage"] = $program->estimated_memory_usage;
        $schedules["schedules"][$rpid]["programs"][$pid]["estTime"] = $program->estimated_time;
        $schedules["schedules"][$rpid]["programs"][$pid]["path"] = $program->path;
        $schedules["schedules"][$rpid]["programs"][$pid]["cmdLine"] = $program->command_line;

    }

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
                $schedules["schedules"][$rpid_parsed]["days"] = array(
                    1 => "sunday",
                    2 => "monday",
                    3 => "tuesday",
                    4 => "wednesday",
                    5 => "thursday",
                    6 => "friday",
                    7 => "saturday"
                );

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

        }

        return $schedules;

    }

    public function updateJson(){
        //With the database updated, the JSON needs to be updated as well

        //Delete spydr.json if it exists, as well as make sure it is deleted afterwards,
        //since File::delete() does not check for deletion
        $filename = storage_path("../../threadTesting/spydr.json");
        while (File::exists($filename)){
            File::delete($filename);
        }

        //Create the content of spydr.json
        $spydr = json_encode($this->createJson(), JSON_PRETTY_PRINT);

        //Replace the previous spydr.json with the updated version
        File::put($filename, $spydr);

    }

}