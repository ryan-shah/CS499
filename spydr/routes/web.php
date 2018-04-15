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

Route::post('/add-program', 'ProgramController@addNewProgram');
Route::post('/get-program/{id}', 'ProgramController@displayProgramInfo');
Route::post('/edit-program', 'ProgramController@editProgram');
Route::post('/get-program-list', 'ProgramController@getAllPrograms');
Route::post('/add-runlist', 'RunlistController@addRunlist');

Route::get('/login', function () {
    return view('login');
});

