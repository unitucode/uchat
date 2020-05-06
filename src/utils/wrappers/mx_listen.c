#include "utils.h"

/*
 * Wrapper of standart function listen
 */
int mx_listen(int socket, int backlog) {
    char *env_backlog = getenv("LISTENQ");
    int result = 0;

    if (env_backlog) {
        backlog = atoi(env_backlog);
        mx_logger(MX_LOG_FILE, LOGMSG, "got %s\n", env_backlog);
    }
    result = listen(socket, backlog);
    if (result < 0)
        mx_elogger(MX_LOG_FILE, LOGERR, "listen\n");
    return result;
}
