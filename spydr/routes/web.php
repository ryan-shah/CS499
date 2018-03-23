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
    $programs = array(
                    array(
                        'program_id' => 1,
                        'program_name' => 'Program',
                        'program_memory' => '140MB',
                        'program_cpu_time' => '00:05:00',
                        'program_path' => 'path/to/program/one'
                    ),

                    array(
                        'program_id' => 2,
                        'program_name' => 'Some Script',
                        'program_memory' => '10MB',
                        'program_cpu_time' => '00:25:00',
                        'program_path' => 'path/to/program/two'
                    ),

                    array(
                        'program_id' => 3,
                        'program_name' => 'Another Thing',
                        'program_memory' => '6.3MB',
                        'program_cpu_time' => '01:05:30',
                        'program_path' => 'path/to/program/two'
                    )
    );



    return view('home', ['programs' => $programs]);
});

Route::get('/login', function () {
    return view('login');
});