#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define LOG_OUT_CONSOLE 0b00000001
#define LOG_OUT_FILE	0b00000010

#define CFG_KEY "LogLevel"

typedef enum
{
	LOG_TRACE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL
} LogLevel;

static const char *level_names[] = {
  "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

typedef enum {
	LOG_CTRL_ENV,
	LOG_CTRL_MANUAL,
	LOG_CTRL_CFG,
} LogCtrlMode;

struct LogContext
{
	LogCtrlMode ctrlmode;
	LogLevel level;
	LogLevel cfglevel;
	char env[32];
	char cfg[32];
	char outmode;
	char logpath[256];
	FILE *fd;
};

struct LogContext g_ctx = {
	LOG_CTRL_MANUAL,
	LOG_INFO,
	LOG_INFO,
	"",
	"",
	LOG_OUT_CONSOLE,
	"",
	NULL
};

char *trim(char *str)
{
	char *p = str;
	char *p1;
	if(p)
	{
		p1 = p + strlen(str) - 1;
		while(*p && isspace(*p)) p++;
		while(p1 > p && isspace(*p1)) *p1 = '\0';
	}
	return p;
}

void log4c_read_cfg(char *cfg)
{
	FILE *fd = NULL;
	char line[1024] = {0};
	fd = fopen(cfg, "r");
	if(NULL == fd) return;

	char value[32] = {0};
	while(!feof(fd)){
		fgets(line, 1024, fd);
		char *key = strstr(line, CFG_KEY);
		if(NULL == key) continue;

		char *equal = strstr(key, "="); 
		if(NULL == equal)  continue;

		if(0 == strlen(equal)) continue;

		strcpy(value, equal+1);
		char *trimvalue = trim(value);

		if(0 == strcmp(trimvalue, "trace")){
			g_ctx.cfglevel = LOG_TRACE;
		}
		else if(0 == strcmp(trimvalue, "debug")){
			g_ctx.cfglevel = LOG_DEBUG;
		}
		else if(0 == strcmp(trimvalue, "info")){
			g_ctx.cfglevel = LOG_INFO;
		}
		else if(0 == strcmp(trimvalue, "warn")){
			g_ctx.cfglevel = LOG_WARN;
		}
		else if(0 == strcmp(trimvalue, "error")){
			g_ctx.cfglevel = LOG_ERROR;
		}
		else if(0 == strcmp(trimvalue, "fatal")){
			g_ctx.cfglevel = LOG_FATAL;
		}
	}
}

/*
 * export ENV_NAME=$(ENV_VALUE)
 * ENV_VALUE:	1		2		3		4		5		6
 * LOG_LEVEL:	FATAL	ERROR	WARN	INFO	DEBUG	TRACE
 */
void log4c_set_log_env(char *env)
{
	g_ctx.ctrlmode = LOG_CTRL_ENV;
	strcpy(g_ctx.env, env);
}

void log4c_set_log_level(LogLevel level)
{
	g_ctx.ctrlmode  = LOG_CTRL_MANUAL;
	g_ctx.level = level;
}

void log4c_set_log_cfg(char *cfg)
{
	g_ctx.ctrlmode = LOG_CTRL_CFG;
	strcpy(g_ctx.cfg, cfg);

	log4c_read_cfg(g_ctx.cfg);
}

void log4c_set_logpath(char *path)
{
	strcpy(g_ctx.logpath, path);
	if(0 != strcmp(g_ctx.logpath, ""))
	{
		g_ctx.fd = fopen(g_ctx.logpath, "w+");
		if(NULL == g_ctx.fd) {
			printf("fail to open logfile %s\n", g_ctx.logpath);	
		}
	}
}

void log4c_init()
{
}

void log4c_deinit()
{
	if(g_ctx.fd) fclose(g_ctx.fd);
}

void log4c_set_out_mode(char mode)
{
	g_ctx.outmode = mode;
}

#define log4c_t(...) log4c(LOG_TRACE, __VA_ARGS__)
#define log4c_d(...) log4c(LOG_DEBUG, __VA_ARGS__)
#define log4c_i(...)  log4c(LOG_INFO, __VA_ARGS__)
#define log4c_w(...)  log4c(LOG_WARN, __VA_ARGS__)
#define log4c_e(...) log4c(LOG_ERROR, __VA_ARGS__)
#define log4c_f(...) log4c(LOG_FATAL, __VA_ARGS__)

int log4c_check(LogLevel level)
{
	if(LOG_CTRL_ENV == g_ctx.ctrlmode)
	{
		/* dynamic log base on env */
		char *s = NULL;
		s = getenv(g_ctx.env);
		if(NULL == s) return 0;

		int env = atoi(s);
		LogLevel env_level = LOG_INFO;
		if(1 == env){
			env_level = LOG_FATAL;
		}
		else if(2 == env){
			env_level = LOG_ERROR;
		}
		else if(3 == env){
			env_level = LOG_WARN;
		}
		else if(4 == env){
			env_level = LOG_INFO;
		}
		else if(5 == env){
			env_level = LOG_DEBUG;
		}
		else if(6 == env){
			env_level = LOG_FATAL;
		}

		if (level < env_level) {
			return 0;
		}
	}
	else if(LOG_CTRL_MANUAL == g_ctx.ctrlmode)
	{
		if (level < g_ctx.level) {
			return 0;
		}
	}
	else if(LOG_CTRL_CFG == g_ctx.ctrlmode)
	{
		if (level < g_ctx.cfglevel) {
			return 0;
		}
	}

	return 1;
}

void log4c(LogLevel level, const char *fmt, ...)
{
	if(!log4c_check(level)) return;

	time_t t = time(NULL);
	struct tm *lt = localtime(&t);

	char buf_t[32];
	buf_t[strftime(buf_t, sizeof(buf_t), "[%Y-%m-%d %H:%M:%S]", lt)] = '\0';

	char buf[1024] = {0};
	va_list args;
	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);

	printf("%s [%-5s]: %s\n", buf_t, level_names[level], buf);

	if(g_ctx.fd) {
		fprintf(g_ctx.fd, "%s [%-5s]: %s\n", buf_t, level_names[level], buf);
		fflush(g_ctx.fd);
	}
}

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
