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

/**
 * Sets the global log level for the logger.
 *
 * @param level The log level to set. Possible values are LOG_DEBUG, LOG_INFO,
 * LOG_WARN, and LOG_ERROR. Messages below this level will not be logged.
 */
void set_log_level(int level);

/**
 * Opens the log file for appending log messages.
 *
 * @details
 * This function attempts to open the log file specified by LOG_FILE_NAME
 * in append mode. If the file cannot be opened, an error message is printed
 * to stderr.
 */
void open_log_file();

/**
 * Close the log file if it is open. This should be called when the program is
 * about to exit to ensure that the log file is properly closed.
 *
 * @details
 * If the log file is not open, this function does nothing.
 */
void close_log_file();

/**
 * Logs a message with the given level and format string to the console and to
 * the log file. If the level is less than the current log level, the message is
 * not logged. The message is formatted according to fmt and varargs, and is
 * prefixed with a timestamp and a string corresponding to the log level.
 *
 * @param level The log level to log the message at. Possible values are
 * LOG_DEBUG, LOG_INFO, LOG_WARN, and LOG_ERROR.
 * @param fmt The format string for the message to log
 * @param ... The variadic arguments to format the string with
 */
void log_message(int level, const char* fmt, ...);
