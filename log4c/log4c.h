#ifndef LOG4C_H
#define LOG4C_H

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


/*
 * export ENV_NAME=$(ENV_VALUE)
 * ENV_VALUE:	1		2		3		4		5		6
 * LOG_LEVEL:	FATAL	ERROR	WARN	INFO	DEBUG	TRACE
 */
void log4c_set_log_env(char *env);

void log4c_set_log_level(LogLevel level);

void log4c_set_log_cfg(char *cfg);

void log4c_set_logpath(char *path);

void log4c_init();

void log4c_deinit();

void log4c(LogLevel level, const char *fmt, ...);

#define log4c_t(...) log4c(LOG_TRACE, __VA_ARGS__)
#define log4c_d(...) log4c(LOG_DEBUG, __VA_ARGS__)
#define log4c_i(...)  log4c(LOG_INFO, __VA_ARGS__)
#define log4c_w(...)  log4c(LOG_WARN, __VA_ARGS__)
#define log4c_e(...) log4c(LOG_ERROR, __VA_ARGS__)
#define log4c_f(...) log4c(LOG_FATAL, __VA_ARGS__)


#endif
