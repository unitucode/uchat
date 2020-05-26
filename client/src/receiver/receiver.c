#include "client.h"

void mx_init_receiver(t_chat *chat) {
    pthread_t tid;
    chat->request_handler[MX_TOKEN] = mx_authorization;
    mx_pthread_create(&tid, NULL, mx_receiver, chat);
}

void *mx_receiver(void *arg) {
    t_chat *chat = (t_chat*)arg;
    t_dtp *data = NULL;

    while ((data = mx_recv(chat->ssl))) {
        if (!mx_error_handle(data, chat))
            if (!mx_authorization(data, chat))
                break;
        if (chat->auth_token)
            if (!chat->request_handler[data->type](data, chat))
                break;
        mx_free_request_struct(&data);
    }
    mx_free_request_struct(&data);
    return NULL;
}
