#include "utils.h"

/*
 * Wrapper of standart function accept
 */
int mx_accept(int socket, struct sockaddr *restrict address,
              socklen_t *restrict address_len) {
    int result = 0;

    while ((result = accept(socket, address, address_len)) < 0) {
        if (errno == ECONNABORTED)
            continue;
        else
            mx_elogger(MX_LOG_FILE, LOGERR, "accept\n");
    }
    return result;
}
