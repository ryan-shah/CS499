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
//        // Add stuff for dependencies too
//
        $program->save();

        $response = array(
            'status' => 'success',
            'msg' => $request->input('name'),
        );

        return response()->json($response);

        }
}
