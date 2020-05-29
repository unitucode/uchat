#include "client.h"

t_queue_data *mx_new_queue_data(t_dtp *data, t_chat *chat) {
    t_queue_data *new_queue_data = mx_malloc(sizeof(t_queue_data));

    new_queue_data->data = data;
    new_queue_data->chat = chat;
    return new_queue_data;
}

void mx_delete_queue_data(t_queue_data **data) {
    if (data && *data) {
        mx_free_request(&(*data)->data);
        mx_free((void**)data);
        *data = NULL;
    }
}
