#include "utils.h"

/*
 * Wrapper of standart function getaddrinfo
 */
int mx_getaddrinfo(const char *hostname, const char *servname,
                   const struct addrinfo *hints, struct addrinfo **res) {
    int result = getaddrinfo(hostname, servname, hints, res);

    if (result)
        mx_elogger(MX_LOG_FILE, LOGERR, "getaddrinfo\n");
    return result;
}
