#include "utils.h"

/*
 * Write current time to log
 */
void mx_log_time(FILE *fd) {
    long ttime = time(NULL);
    char *stime = ctime(&ttime);
    char *rtime = strndup(stime, strlen(stime) - 1);

    fprintf(fd, "%s\t", rtime);
    free(rtime);
}

/*
 * Write type to log
 */
void mx_log_type(FILE *fd, t_logtype type) {
    if (type == LOGMSG)
        fprintf(fd, "MESSAGE: ");
    else if (type == LOGWAR)
        fprintf(fd, "WARNING: ");
    else if (type == LOGERR)
        fprintf(fd, "ERROR: ");
}
