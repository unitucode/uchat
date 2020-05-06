#include "utils.h"

/*
 * Write current time to the log
 */
void mx_log_time(FILE *fd) {
    long ttime = time(NULL);
    char *stime = ctime(&ttime);
    char *rtime = strndup(stime, strlen(stime) - 1);

    fprintf(fd, "[%s] ", rtime);
    free(rtime);
}

/*
 * Write type to the log
 */
void mx_log_type(FILE *fd, t_logtype type) {
    if (type == LOGMSG)
        fprintf(fd, "MESSAGE: ");
    else if (type == LOGWAR)
        fprintf(fd, "WARNING: ");
    else if (type == LOGERR)
        fprintf(fd, "ERROR: ");
}

/*
 * If there is errno, write it to the log
*/
void mx_log_errno(FILE *fd) {
    if (errno != 0) {
        fprintf(fd, "[ERRNO is %d: %s] ", errno, strerror(errno));
        errno = 0;
    }
}
