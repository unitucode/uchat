#include "utils.h"

/*
 * Write pid and pgid to the log
 */
void mx_log_id(FILE *fd) {
    int pid = getpid();
    int pgid = getpgid(pid);

    if (pgid == -1) {
        fprintf(stderr, "Logger error: getpgid problem\n");
        exit(errno);
    }
    fprintf(fd, "[pid: %d|pgid: %d]", pid, pgid);
}

/*
 * Write current time to the log
 */
void mx_log_time(FILE *fd) {
    long ttime = time(NULL);
    char *stime;
    char *rtime;

    if (ttime == -1) {
        fprintf(stderr, "Logger error: time problem\n");
        exit(errno);
    }
    stime = ctime(&ttime);
    if (stime == NULL) {
        fprintf(stderr, "Logger error: ctime problem\n");
        exit(errno);
    }
    rtime = strndup(stime, strlen(stime) - 1);
    fprintf(fd, "[%s] ", rtime);
    mx_free((void **)&rtime);
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
