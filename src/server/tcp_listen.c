#include "server.h"

/*
 * Listens to socket and port
 * Works with IPv4 and IPv6
 */
int mx_tcp_listen(const char *serv, socklen_t *addr_len) {
    int listen_fd, n;
    const int on = 1;
    struct addrinfo	hints, *res = NULL, *ressave = NULL;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((n = getaddrinfo(NULL, serv, &hints, &res)) != 0) {
        fprintf(stderr, "tcp_listen error\n");
        exit(1);
    }

    do {
        listen_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listen_fd < 0)
            continue;
        t_sockopt sockopt;
        sockopt.socket = listen_fd;
        sockopt.level = SOL_SOCKET;
        sockopt.option_name = SO_REUSEADDR;
        sockopt.option_value = &on;
        sockopt.option_len = sizeof(on);
        mx_setsockopt(&sockopt);
        if (bind(listen_fd, res->ai_addr, res->ai_addrlen) == 0)
            break;
        mx_close(listen_fd);
    } while ((res = res->ai_next) != NULL);

    if (res == NULL)
        exit(1);

    mx_listen(listen_fd, MX_LISTENQ);

    if (addr_len)
        *addr_len = res->ai_addrlen;
    
    freeaddrinfo(ressave);
    return listen_fd;
}
