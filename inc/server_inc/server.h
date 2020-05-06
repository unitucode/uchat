#pragma once

#include "../utils_inc/utils.h"

#define MX_LISTENQ 1024
#define MX_PORT_LEN 8

typedef struct s_client {
    struct sockaddr *cliaddr;
    socklen_t len;
    char ip[INET6_ADDRSTRLEN];
    char port[MX_PORT_LEN];
    int socket_fd;
}              t_client;

int mx_tcp_listen(const char *serv, socklen_t *addr_len);
void mx_get_client_info(t_client *client);
t_client *mx_new_client(socklen_t len);
void mx_delete_client_list(t_list *list, t_client *client);
