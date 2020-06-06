#include "client.h"

void mx_init_receiver(t_chat *chat) {
    pthread_t tid;
    chat->request_handler[RQ_TOKEN] = mx_authorization;
    chat->request_handler[RQ_ERROR_MSG] = mx_error_handle;
    chat->request_handler[RQ_LOG_IN] = NULL;
    chat->request_handler[RQ_SIGN_UP] = NULL;
    mx_pthread_create(&tid, NULL, mx_receiver, chat);
}

void *mx_receiver(void *arg) {
    t_chat *chat = (t_chat*)arg;
    t_dtp *data = NULL;

    while ((data = mx_recv(chat->ssl))) {
        if (chat->auth_token
            || data->type == RQ_ERROR_MSG
            || data->type == RQ_TOKEN) {
            if (!chat->request_handler[data->type]
                ||!chat->request_handler[data->type](data, chat)) {
                break;
            }
        }
        mx_free_request(&data);
    }
    mx_free_request(&data);
    return NULL;
}
