#include "server.h"

void mx_send_to_all(t_dtp *data, t_client *client) {
    t_node *cur_node = NULL;
    t_client *cur_client = NULL;

    mx_pthread_mutex_lock(&client->chat->mutex);
    cur_node = client->chat->clients->back;
    while (cur_node) {
        cur_client = (t_client*)cur_node->data;
        if (cur_client->user)
            mx_send(cur_client->ssl, data);
        cur_node = cur_node->next;
    }
    mx_pthread_mutex_unlock(&client->chat->mutex);
}
