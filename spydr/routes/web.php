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

Route::get('/', function () {

    $programs = DB::select('select * from programs');

    return view('home', ['programs' => $programs]);
});

Route::post('/', 'ProgramController@testfunction');


Route::get('/login', function () {
    return view('login');
});

