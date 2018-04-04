<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateDependenciesTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('dependencies', function (Blueprint $table) {
            $table->increments('did');
            $table->unsignedInteger('program_id');
            $table->unsignedInteger('dependency_id');
            $table->timestamps();
        });

        Schema::table('dependencies', function($table) {
            $table->foreign('program_id')->references('pid')->on('programs');
            $table->foreign('dependency_id')->references('pid')->on('programs');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('dependencies');
    }
}
