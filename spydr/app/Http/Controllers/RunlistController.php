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

    // Takes in a request that looks very similar to the "addProgram" one, but this one adds a new runlist
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

    public function getRunlist(Request $request, $id){
        // Get a runlist from the database by its id
        $runlist = RunlistParameter::find($id);
        $response = array(
            'status' => 'success',
            'runlist' => $runlist
        );

        return response()->json($response);
    }

    public function deleteRunlist(Request $request) {
        // Delete a runlist with the requested id
        RunlistParameter::destroy($request->input('rpid'));

        $response = array(
            'status' => $request->input('rpid'),
        );

        //Update spydr.json with the new information
        app('App\Http\Controllers\JsonController')->updateJson();

        return response()->json($response);
    }
}
