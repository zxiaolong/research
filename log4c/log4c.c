#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOG_OUT_CONSOLE 0b00000001
#define LOG_OUT_FILE	0b00000010

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
	char env[32];
	char cfg[32];
	char outmode;
};

struct LogContext g_ctx = {
	LOG_CTRL_MANUAL,
	LOG_INFO,
	"",
	"",
	LOG_OUT_CONSOLE
};

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
		return 0;
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
}

int main(int argc, char argv[])
{
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

	log4c_set_log_cfg("/etc/log4c.cfg");

	log4c_t("%s", "trace info");
	log4c_d("%s", "debug info");
	log4c_i("%s", "info info");
	log4c_w("%s", "warn info");
	log4c_e("%s", "error info");
	log4c_f("%s", "fatal info");

	return 0;
}
