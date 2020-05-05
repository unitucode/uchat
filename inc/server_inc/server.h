#pragma once

#include "../utils_inc/utils.h"

#define MX_LISTENQ 1024

typedef struct s_client {
    struct sockaddr *cliaddr;
    socklen_t len;
    char ip[INET_ADDRSTRLEN];
    char port[8];
    int socket_fd;
}              t_client;

int mx_tcp_listen(const char *serv, socklen_t *addr_len);
void mx_get_client_info(t_client *client);
t_client *mx_new_client();
