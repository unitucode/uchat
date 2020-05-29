#include "client.h"

void mx_init_receiver(t_chat *chat) {
    pthread_t tid;
    chat->request_handler[RQ_TOKEN] = mx_authorization;
    chat->request_handler[RQ_ERROR_MSG] = mx_error_handle;
    chat->request_handler[RQ_LOG_IN] = NULL;
    chat->request_handler[RQ_SIGN_UP] = NULL;
    chat->request_handler[RQ_NEW_ROOM] = mx_new_room;
    mx_pthread_create(&tid, NULL, mx_receiver, chat);
}

void *mx_receiver(void *arg) {
    t_chat *chat = (t_chat*)arg;

    while ((chat->data = mx_recv(chat->ssl))) {
        printf("recv = %s", chat->data->str);
        // if (chat->auth_token
        //     || chat->data->type == RQ_ERROR_MSG
        //     || chat->data->type == RQ_TOKEN) {
        //     if (!chat->request_handler[chat->data->type]
        //         ||!chat->request_handler[chat->data->type](chat->data, chat)) {
        //         break;
        //     }
        // }
        // mx_free_request(&chat->data);
    }
    mx_free_request(&chat->data);
    printf("Closed receiver\n");
    return NULL;
}
