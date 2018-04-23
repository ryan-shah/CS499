<?php

namespace App\Http\Controllers;

use App\RunlistParameter;
use Illuminate\Http\Request;

class RunlistController extends Controller
{
    // Handles any making/editing of runlists

    public function readRunlists(){

        $runlists = RunlistParameter::all();
        return $runlists;

    }

    public function addRunlist(Request $request){

        // Takes in a request that looks very similar to the "addProgram" one, but this one adds a new runlist

        $runlist_parameter = new RunlistParameter;

        $runlist_parameter->rname = $request->input('name');
        $runlist_parameter->rtime = $request->input('time');
        $runlist_parameter->days = $request->input('days');

        $runlist_parameter->save();

        $response = array(
            'status' => 'success',
            'msg' => $request->all(),
        );

        //Update spydr.json with the new information
        app('App\Http\Controllers\JsonController')->updateJson();

        return response()->json($response);

    }

    public function getAllRunlists(Request $request){
        $runlists = RunlistParameter::select('rpid', 'rname')->get();
        $response = array(
            'status' => 'success',
            'runlists' => $runlists
        );

        return response()->json($response);
    }
}
