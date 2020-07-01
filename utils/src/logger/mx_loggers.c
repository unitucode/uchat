#include <glib/gprintf.h>
#include "utils.h"
#include "unistd.h"

static void log_lvl(FILE *fd, GLogLevelFlags flags) {
    if (flags == G_LOG_LEVEL_WARNING)
        g_fprintf(fd, "WARNING  ");
    else if (flags == G_LOG_LEVEL_MESSAGE)
        g_fprintf(fd, "MESSAGE  ");
    else if (flags == G_LOG_LEVEL_ERROR)
        g_fprintf(fd, "ERROR  ");
}

/*
 * Logs string to file
 */

void mx_logger(gchar *file_name, GLogLevelFlags flags, gchar *error) {
    FILE *fd = fopen(file_name, "a");
    gchar *date = NULL;
    GDateTime *dt = g_date_time_new_now_local();

    date = g_date_time_format(dt, "%T %e.%m.%Y");
    g_fprintf(fd, "date:%s  ", date);
    g_fprintf(fd, "pid:%d  ", getpid());
    log_lvl(fd, flags);
    g_fprintf(fd, "'%s'\n", error);
    g_free(date);
    fclose(fd);
    if (flags == G_LOG_LEVEL_ERROR)
        exit(1);
}
