<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateRunlistsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('runlists', function (Blueprint $table) {
            $table->increments('rid');
            $table->unsignedInteger('runlist_id');
            $table->unsignedInteger('program_id');
            $table->timestamps();
        });

        Schema::table('runlists', function($table) {
            $table->foreign('program_id')->references('pid')->on('programs');
            $table->foreign('runlist_id')->references('rpid')->on('runlist_parameters');
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('runlists');
    }
}
