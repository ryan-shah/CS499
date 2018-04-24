<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Dependency extends Model
{
    // Creates a model for dependencies from the database. Lookup "Laravel Eloquent ORM for more details.
    protected $table = 'dependencies';
    protected  $primaryKey = 'did';
}
