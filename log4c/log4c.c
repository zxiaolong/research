#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };
static int log4c_level = LOG_TRACE;

static const char *level_names[] = {
  "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

#define log4c_t(...) log4c(LOG_TRACE, __VA_ARGS__)
#define log4c_d(...) log4c(LOG_DEBUG, __VA_ARGS__)
#define log4c_i(...)  log4c(LOG_INFO, __VA_ARGS__)
#define log4c_w(...)  log4c(LOG_WARN, __VA_ARGS__)
#define log4c_e(...) log4c(LOG_ERROR, __VA_ARGS__)
#define log4c_f(...) log4c(LOG_FATAL, __VA_ARGS__)

void log4c(int level, const char *fmt, ...)
{
	if (level < log4c_level) {
		return;
	}

	time_t t = time(NULL);
	struct tm *lt = localtime(&t);

	char buf[32];
	buf[strftime(buf, sizeof(buf), "[%Y-%m-%d %H:%M:%S]", lt)] = '\0';
	fprintf(stderr, "%s [%-5s]: ", buf, level_names[level]);

	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	fprintf(stderr, "\n");
	fflush(stderr);
}

int main(int argc, char argv[])
{
	log4c_level = LOG_INFO;
	log4c_t("%s", "trace info");
	log4c_d("%s", "debug info");
	log4c_i("%s", "info info");
	log4c_w("%s", "warn info");
	log4c_e("%s", "error info");
	log4c_f("%s", "fatal info");
	return 0;
}
