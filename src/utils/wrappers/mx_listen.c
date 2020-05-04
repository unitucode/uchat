#include "utils.h"

/*
 * Wrapper of standart function socket
 */
int mx_listen(int socket, int backlog) {
    char *env_backlog = getenv("LISTENQ");
    int result = 0;

    if (env_backlog)
        backlog = atoi(env_backlog);

    result = listen(socket, backlog);
    if (result < 0) {
        //error
    }
    return result;
}
