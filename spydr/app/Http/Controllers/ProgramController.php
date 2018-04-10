<?php

namespace App\Http\Controllers;

use App\Program;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;

class ProgramController extends Controller
{
    //
    public function testfunction(Request $request){
        if ($request->isMethod('post')){
            return response()->json(['response' => 'This is post method']);
        }

        return response()->json(['response' => 'This is get method']);
    }

    public function addNewProgram(Request $request){
        // At this point, jQuery has given us all of the information we need to make a new
        // entry in the database.

        $program = new Program;
        $program->pname = $request->input('name');
        $program->estimated_memory_usage = $request->input('memUsage');
        $program->estimated_time = 0;
        $program->path = $request->input('path');
        $program->command_line = $request->input('args');

//
//        // Add stuff for dependencies, run lists eventually
//
        $program->save();

        $response = array(
            'status' => 'success',
            'msg' => $request->input('name'),
        );

        return response()->json($response);
    }

    public function displayProgramInfo(Request $request, $id){
        // This is for when you want to edit a program that already exists - we want to get the information from the
        // programs table to populate the modal

        $program = Program::find($id);

        $response = array(
            'status' => 'success',
            'program' => json_encode($program), // Pass back the program as a json, to be easily parsed by jQuery
        );

        return response()->json($response);
    }

    public function editProgram(Request $request){
        // Very similar to adding, except this time we just want to update.
        $program = Program::find($request->input('pid'));
        $program->pname = $request->input('name');
        $program->estimated_memory_usage = $request->input('memUsage');
        $program->estimated_time = 0;
        $program->path = $request->input('path');
        $program->command_line = $request->input('args');

        $program->save();

        $response = array(
            'status' => 'success',
        );

        return response()->json($response);
    }
}
