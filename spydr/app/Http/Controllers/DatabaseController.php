<?php

namespace App\Http\Controllers;

use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\File;

class DatabaseController extends Controller
{

    public function updateDatabase(){

        //With the c++ program creating a JSON with updated expected_memory_usage and expected_time,
        //we should update the database with that information

        //Read and convert output.json into an array
        $filename = storage_path("../../server/output.json");
        $input = json_decode(File::get($filename), TRUE);

        //Iterate through each program
        foreach($input["programs"] as $program) {

            //Update each program ran with their new runtime and memory usage
            DB::table('programs')
                ->where('pid', $program["id"])
                ->update(['estimated_memory_usage' => $program["estMemUsage"]]);

            DB::table("programs")
                ->where('pid', $program["id"])
                ->update(['estimated_time' => $program["estTime"]]);
        }

        //Update spydr.json with the new information
        app('App\Http\Controllers\JsonController')->updateJson();

    }

}
