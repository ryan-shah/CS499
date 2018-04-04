<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

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
        if ($request->isMethod('post')){
            // At this point, jQuery has given us all of the information we need to make a new
            // entry in the database.
            $response = array(
                'status' => 'success',
                'msg' => 'Setting created successfully',
            );

            return response()->json($response);

        }
    }
}
