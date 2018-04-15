<?php

namespace App\Http\Controllers;

use App\Dependency;
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
        $program->estimated_memory_usage = $request->input('memUsage', 0);
        $program->estimated_time = 0;
        $program->path = $request->input('path');
        $program->command_line = $request->input('args', '<none>');

        $program->save();

        $pid = $program->pid;

        $dependencies = json_decode($request->input('dependencies'));

        // Add stuff for dependencies, run lists eventually
        foreach($dependencies as $dep){
            // Each dependency is its own entry in the request, and will become a new row in the table.
            $dependency = new Dependency;
            $dependency->program_id = $pid;
            $dependency->dependency_id = $dep;

            $dependency->save();
        }


        $response = array(
            'status' => 'success',
            'msg' => $request->all(),
            'deps' => $dependencies,
            'pid' => $pid,
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

    public function getAllPrograms(Request $request){
        $programs = Program::select('pid', 'pname')->get();
        $response = array(
            'status' => 'success',
            'programs' => $programs
        );

        return response()->json($response);
    }
}
