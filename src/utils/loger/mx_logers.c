#include "utils.h"

/*
 * Loging string to file
 */
void mx_loger(const char *file, t_logtype type, const char *fmt, ...) {
    va_list ap;
    FILE *fd;

    if (file == NULL)
        fd = stderr;
    else
        fd = fopen(file, "a");
    mx_log_time(fd);
    mx_log_type(fd, type);
    va_start(ap, fmt);
    vfprintf(fd, fmt, ap);
    va_end(ap);
    fclose(fd);
}

/*
 * Loging string to file with exit
 */
void mx_eloger(const char *file, t_logtype type, const char *fmt, ...) {
    va_list ap;
    FILE *fd;

    if (file == NULL)
        fd = stderr;
    else
        fd = fopen(file, "a");
    mx_log_time(fd);
    mx_log_type(fd, type);
    va_start(ap, fmt);
    vfprintf(fd, fmt, ap);
    va_end(ap);
    exit(1);
}
