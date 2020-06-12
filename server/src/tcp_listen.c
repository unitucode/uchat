#include "server.h"

/*
 * Sets socket and validates
 */
static bool set_socket(int *lis_fd, struct addrinfo *res) {
    *lis_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (*lis_fd < 0)
        return true;
    return false;
}

/*
 * Initialization sockopt for setsockopt
 */
static void init_sockopt(int fd, const int on) {
    t_sockopt sockopt;

    sockopt.socket = fd;
    sockopt.level = SOL_SOCKET;
    // sockopt.option_name = SO_REUSEADDR;
    #ifdef SO_NOSIGPIPE
        sockopt.option_name = SO_NOSIGPIPE;
    #else
        signal(SIGPIPE, SIG_IGN); // for linux
    #endif
    sockopt.option_value = &on;
    sockopt.option_len = sizeof(on);
    mx_setsockopt(&sockopt);
}

/*
 * Initialization res for addrinfo
 */
static struct addrinfo *init_res(const char *serv) {
    struct addrinfo *res;
    struct addrinfo hints;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    mx_getaddrinfo(NULL, serv, &hints, &res);
    return res;
}

/*
 * Listens to socket and port
 * Works with IPv4, IPv6 and domens
 */
int mx_tcp_listen(const char *serv, socklen_t *addr_len) {
    int lis_fd = 0;
    const int on = 1;
    struct addrinfo	*res_save = init_res(serv);
    struct addrinfo *res = NULL;

    for (res = res_save; res; res = res->ai_next) {
        if (set_socket(&lis_fd, res))
            continue;
        init_sockopt(lis_fd, on);
        if (!bind(lis_fd, res->ai_addr, res->ai_addrlen))
            break;
        mx_close(lis_fd);
    }
    if (!res)
        mx_elogger(MX_LOG_FILE, LOGERR, "tcp_listen\n");
    mx_listen(lis_fd, MX_LISTENQ);
    if (addr_len)
        *addr_len = res->ai_addrlen;
    freeaddrinfo(res_save);
    return lis_fd;
}
