#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "log4c.h"

int main(int argc, char argv[])
{
	log4c_init();
	log4c_set_log_level(LOG_ERROR);

	log4c_t("%s", "trace info");
	log4c_d("%s", "debug info");
	log4c_i("%s", "info info");
	log4c_w("%s", "warn info");
	log4c_e("%s", "error info");
	log4c_f("%s", "fatal info");
	
	log4c_set_log_env("LOG4C");

	log4c_t("%s", "trace info");
	log4c_d("%s", "debug info");
	log4c_i("%s", "info info");
	log4c_w("%s", "warn info");
	log4c_e("%s", "error info");
	log4c_f("%s", "fatal info");

	log4c_set_log_cfg("log4c.cfg");

	log4c_t("%s", "trace info");
	log4c_d("%s", "debug info");
	log4c_i("%s", "info info");
	log4c_w("%s", "warn info");
	log4c_e("%s", "error info");
	log4c_f("%s", "fatal info");

	log4c_set_logpath("./log4c.log");

	log4c_t("%s", "trace info");
	log4c_d("%s", "debug info");
	log4c_i("%s", "info info");
	log4c_w("%s", "warn info");
	log4c_e("%s", "error info");
	log4c_f("%s", "fatal info");

	log4c_deinit();

	return 0;
}
