#include "server.h"

/*
 * Creates new client
 */
t_client *mx_new_client(socklen_t len) {
    t_client *client = mx_malloc(sizeof(t_client));

    strcpy(client->ip, "-");
    strcpy(client->port, "-");
    client->len = len;
    client->cliaddr = mx_malloc(len);
    client->socket_fd = 0;
    client->user = NULL;
    return client;
}

/*
 * Deletes client
 */
void mx_delete_client(void **data) {
    t_client **client = (t_client**)data;

    if (client && *client) {
        SSL_free((*client)->ssl);
        mx_close((*client)->socket_fd);
        mx_free((void**)&(*client)->cliaddr);
        mx_free((void**)client);
    }
}
