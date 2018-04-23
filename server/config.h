/*
	All constants are defined here. Any changes to wait time or default files or what have you can be made here
*/

#ifndef CONFIG_H
#define CONFIG_H

class Config {
  public:
	//time between checking whether to run schedules
	//in seconds
	int RUN_WAIT_TIME = 5 * 60;

	//default values for input and output files
	string INPUT_FILE_DEFAULT = "spydr.json";
	string OUTPUT_FILE_DEFAULT = "output.json";


	//URL to call when the website needs to read output file
	string WEBSITE_READ_OUTPUT = "https://localhost:8000/output";

};
#endif
