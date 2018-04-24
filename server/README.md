# Welcome to the Server Side of Spydr
To run, do the following things
`$ make`
`$ ./spydr`

Keep in mind, if you don't want to use the default files for spydr (spydr.json for input and output.json for output), please use the `-in </path/to/file>` and `-out <path/to/file>` parameters

## The Following Files are in this directory

### config.h

This file contains the Config class, used to hold any constants the program needs to refer too.
Any changes to the program's wait parameters can be made here.

### json.h

This file contains the readJson and writeJson functions

### program.h

This file contains the Program class and definitions

### schedule.h

This file contains the Schedule class

### schedule.cpp

This file contains the Schedule class definitions and all helper functions
The track_process and Schedule::run() functions, which are the main functions of this program are defined here

### spydr.cpp

This file contains the main() function that checks when to run the schedules and when to read/write output

### Makefile

This file contains the commands to compile the code. `make` will create the spydr program. `make clean` will clean up the executable and output files.

### spydr.json

The default input file

### output.json

The default output file

## The following subdirectories exist

### include/

Contains header files for the [RapidJson library](http://rapidjson.org/)

### scritps

Contains some test scripts
