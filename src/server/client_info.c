#include "server.h"

t_client *mx_new_client(socklen_t len) {
    t_client *client = malloc(sizeof(t_client));

    bzero(client->ip, sizeof(client->ip));
    bzero(client->port, sizeof(client->port));
    client->len = len;
    client->cliaddr = mx_malloc(len);
    client->socket_fd = 0;
    return client;
}

void mx_get_client_info(t_client *client) {
    struct sockaddr_in *sin = (struct sockaddr_in*)client->cliaddr;

    if (!inet_ntop(AF_INET, &sin->sin_addr, client->ip, sizeof(client->ip))) {
        //warning
    }
    if (ntohs(sin->sin_port) != 0) {
        snprintf(client->port, sizeof(client->port), "%d", ntohs(sin->sin_port));
    }
    else {
        //Warning
    }
}
