#include "utils.h"

/*
 * Wrapper of standart function accept
 */
int mx_accept(int socket, struct sockaddr *restrict address,
              socklen_t *restrict address_len) {
    int n = 0;

    while ((n = accept(socket, address, address_len)) < 0) {
        if (errno == ECONNABORTED)
            continue;
        else {
            //error
        }
    }
    return n;
}
