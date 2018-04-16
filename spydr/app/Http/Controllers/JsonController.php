<?php

namespace App\Http\Controllers;

use App\Dependency;
use App\Program;
use App\RunlistParameter;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\File;
use Illuminate\Support\Facades\DB;

class JsonController extends Controller
{

    public function testfunction(Request $request){

        $runlistParameter = RunlistParameter::all();

        //Test out writing to JSON
        $runlistParameterJSON = json_encode($runlistParameter, JSON_PRETTY_PRINT);

        //Change time to hours and minutes, as well as change name

        return $runlistParameterJSON;
    }

    public function updateJson(Request $request){
        //With the database updated, the JSON needs to be updated as well

        //Delete spydr.json if it exists, as well as make sure it is deleted afterwards
        $filename = storage_path("spydr.json");
        while (File::exists($filename)){
            File::delete($filename);
        }

        //Create spydr.json

    }

}
