#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define LOG_FILE_NAME "./logs/log.txt"

#define LOG_DEBUG 0
#define LOG_INFO 1
#define LOG_WARN 2
#define LOG_ERROR 3

void set_log_level(int level);

void log_message(int level, const char* fmt, ...);

void open_log_file();

void close_log_file();