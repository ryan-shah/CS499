<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

use App\Program;
use App\RunlistParameter;

Route::get('/', function () {

    $programs = Program::all();
    $runlist_parameters = RunlistParameter::all();

    return view('home', ['programs' => $programs], ['runlist_parameters' => $runlist_parameters]);
});

// These are routes. When laravel gets a post request at said uri, it executes the action function
Route::post('/add-program', 'ProgramController@addNewProgram');
Route::post('/get-program/{id}', 'ProgramController@displayProgramInfo');
Route::post('/edit-program', 'ProgramController@editProgram');
Route::post('/get-program-list', 'ProgramController@getAllPrograms');
Route::post('/delete-program', 'ProgramController@deleteProgram');

Route::post('/add-runlist', 'RunlistController@addRunlist');
Route::post('/delete-runlist', 'RunlistController@deleteRunlist');
Route::post('/get-runlist/{id}', 'RunlistController@getRunlist');
Route::post('/get-runlist-list', 'RunlistController@getAllRunlists');

//This one is called by the code in /server/ to update the database and spydr.json with updated mem_usage and time values
Route::get('/output', 'DatabaseController@updateDatabase');

Route::get('/login', function () {
    // Unimplemented
    return view('login');
});

