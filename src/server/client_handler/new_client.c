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

void mx_delete_client(t_client **client) {
    SSL_free((*client)->ssl);
    mx_close((*client)->socket_fd);
    free((*client)->cliaddr);
    free(*client);
}

void mx_delete_client_list(t_list *list, t_client *client) {
    t_node *cur = list->head;
    t_node *tmp = NULL;
    t_client *tmp_client = (t_client*)cur->data;

    list->size--;
    if (tmp_client == client) {
        mx_delete_client(&client);
        tmp = list->head;
        list->head = list->head->next;
        free(tmp);
        return;
    }
    for (tmp_client = (t_client *)cur->next->data; cur; cur = cur->next)
        if (tmp_client == client)
            break;
    tmp = cur->next;
    cur->next = tmp->next;
    free(tmp);
    mx_delete_client(&client);
}
