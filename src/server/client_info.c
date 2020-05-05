#include "server.h"

t_client *mx_new_client() {
    t_client *client = malloc(sizeof(t_client));

    bzero(client->ip, sizeof(client->ip));
    client->len = 0;
    client->cliaddr = NULL;
    client->socket_fd = 0;
    return client;
}

void mx_get_client_info(t_client *client) {
    struct sockaddr_in *sin = (struct sockaddr_in *) client->cliaddr;

    if (!inet_ntop(AF_INET, &sin->sin_addr, client->ip, sizeof(client->ip))) {
        //warning
    }
}
