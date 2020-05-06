#include "server.h"

/*
 * Creates new client
 */
t_client *mx_new_client(socklen_t len) {
    t_client *client = malloc(sizeof(t_client));

    strcpy(client->ip, "-");
    strcpy(client->port, "-");
    client->len = len;
    client->cliaddr = mx_malloc(len);
    client->socket_fd = 0;
    return client;
}
