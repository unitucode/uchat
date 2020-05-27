#include "server.h"

void mx_init_receiver(t_chat *chat) {
    chat->request_handler[RQ_SIGN_UP] = mx_sign_up;
    chat->request_handler[RQ_TOKEN] = mx_log_in_token;
    chat->request_handler[RQ_LOG_IN] = mx_log_in;
}

void *mx_receiver(void *arg) {
    t_client *client = (t_client*)arg;
    t_dtp *data = NULL;
    // system("leaks -q uchat_server");

    while ((data = mx_recv(client->ssl))) {
        if (client->user || data->type == RQ_LOG_IN || data->type == RQ_SIGN_UP
            || data->type == RQ_TOKEN) {
            if (!client->chat->request_handler[data->type]
                || !client->chat->request_handler[data->type](data, client)) {
                    break;
            }
        }
        printf("recv = %s\n", data->str);
        // send_to_all(client->chat->clients, client->chat, client, dtp->str);
        mx_free_request_struct(&data);
    }
    mx_free_request_struct(&data);
    mx_disconnect_client(client);
    return NULL;
}
