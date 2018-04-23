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
            $table->unsignedInteger('program_id');
            $table->unsignedInteger('runlist_id');
            $table->timestamps();
        });

        Schema::table('runlists', function(Blueprint $table) {
            $table->foreign('program_id')->references('pid')->on('programs')->onDelete('cascade');
            $table->foreign('runlist_id')->references('rpid')->on('runlist_parameters')->onDelete('cascade');
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
