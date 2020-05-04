#include "utils.h"

/*
 * Wrapper of standart function socket
 */
int mx_socket(int domain, int type, int protocol) {
    int socket_fd = socket(domain, type, protocol);

    if (socket_fd == -1) {
        //error;
    }
    return socket_fd;
}
