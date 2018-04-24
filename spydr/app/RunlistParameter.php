<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class RunlistParameter extends Model
{
    // Creates a model for the runlist parameter table from the database. Lookup "Laravel Eloquent ORM for more details.
    protected $primaryKey = "rpid";
    protected $table = "runlist_parameters";
}
