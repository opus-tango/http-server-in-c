#include "logging.h"

FILE* log_file = NULL;

pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

int log_level = LOG_DEBUG;  // Should pull from env variables eventually

void set_log_level(int level) { log_level = level; }

void open_log_file() {
    log_file = fopen(LOG_FILE_NAME, "a");
    if (log_file == NULL) {
        perror("Failed to open log file\n");
    }
}

void close_log_file() {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}

void log_message(int level, const char* fmt, ...) {
    if (level < log_level) {
        return;
    }
    char timestamp[32];
    time_t now = time(NULL);
    struct tm* timeinfo = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    char* level_str = level == LOG_DEBUG  ? "DEBUG"
                      : level == LOG_INFO ? "INFO"
                      : level == LOG_WARN ? "WARN"
                                          : "ERROR";

    // Use variadic arguments to format string
    va_list args;
    va_start(args, fmt);

    // Log to console
    fprintf(stderr, "[%s] [%s] ", timestamp, level_str);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    // Reset variadic arguments
    va_end(args);
    va_start(args, fmt);

    // Log to file
    pthread_mutex_lock(&log_mutex);
    if (log_file == NULL) {
        open_log_file();
    }
    if (log_file == NULL) {
        perror("Failed to open log file\n");
    }
    if (log_file != NULL) {
        fprintf(log_file, "[%s] [%s] ", timestamp, level_str);
        vfprintf(log_file, fmt, args);
        fprintf(log_file, "\n");
    }
    fflush(log_file);
    pthread_mutex_unlock(&log_mutex);
    va_end(args);
}