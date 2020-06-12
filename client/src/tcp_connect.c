#include "client.h"

/*
 * Initialization res for addrinfo
 */
struct addrinfo *init_res(const char *host, const char *serv) {
    struct addrinfo *res;
    struct addrinfo hints;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    mx_getaddrinfo(host, serv, &hints, &res);
    return res;
}
/*
 * Connects to ip with port
 * Works with IPv4, IPv6 and domens
 */
int mx_tcp_connect(const char *host, const char *serv) {
    int sockfd = 0;
    struct addrinfo *res_save = init_res(host, serv);
    struct addrinfo *res = NULL;

    for (res = res_save; res; res = res->ai_next) {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd < 0)
            continue;
        if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
            break;
        mx_close(sockfd);
    }
    if (!res) {
        mx_logger(MX_LOG_FILE, LOGERR, "tcp_connect\n");
        return -1;
    }
    freeaddrinfo(res_save);
    return sockfd;
}
