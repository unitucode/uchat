#include "utils.h"

/*
 * Logs string to file
 */
void mx_logger(const char *file, t_logtype type, const char *fmt, ...) {
    va_list ap;
    FILE *fd = NULL;

    if (file == NULL)
        fd = stderr;
    if (fd == stderr
        || (fd = fopen(file, "a")) != NULL) {
        mx_log_time(fd);
        mx_log_errno(fd);
        mx_log_type(fd, type);
        va_start(ap, fmt);
        vfprintf(fd, fmt, ap);
        va_end(ap);
        fclose(fd);
    }
    else {
        perror("Can't open/create logfile");
        errno = 0;
    }
}

/*
 * Logs string to file with exit
 */
void mx_elogger(const char *file, t_logtype type, const char *fmt, ...) {
    va_list ap;
    FILE *fd = NULL;

    if (file == NULL)
        fd = stderr;
    if (fd == stderr
        || (fd = fopen(file, "a")) != NULL) {
        mx_log_time(fd);
        mx_log_errno(fd);
        mx_log_type(fd, type);
        va_start(ap, fmt);
        vfprintf(fd, fmt, ap);
        va_end(ap);
        exit(1);
    }
    else {
        perror("Can't open/create logfile");
        errno = 0;
    }
}
