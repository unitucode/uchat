#include "client.h"

void mx_init_receiver(t_chat *chat) {
    pthread_t tid;
    chat->request_handler[RQ_TOKEN] = mx_authorization;
    chat->request_handler[RQ_ERROR_MSG] = mx_error_handle;
    chat->request_handler[RQ_LOG_IN] = NULL;
    chat->request_handler[RQ_SIGN_UP] = NULL;
    chat->request_handler[RQ_GET_ROOMS] = mx_rooms_hanlder;
    chat->request_handler[RQ_GET_NEW_MSGS] = mx_new_msgs_hanlder;
    chat->request_handler[RQ_NEW_ROOM] = mx_new_room;
    chat->request_handler[RQ_USERS_ONLINE] = mx_update_users;
    chat->request_handler[RQ_MSG] = mx_msg;
    chat->request_handler[RQ_LOG_OUT] = mx_log_out;
    mx_pthread_create(&tid, NULL, mx_receiver, chat);
}


void *mx_receiver(void *arg) {
    t_chat *chat = (t_chat*)arg;
    t_dtp *data = NULL;

    while ((data = mx_recv(chat->ssl)) && chat->valid) {
        // printf("get date = %ld\n", time(NULL));
        printf("recv = %s", cJSON_Print(data->json));
        if (g_async_queue_length(chat->queue) > MX_MAX_LENGTH_QUEUE)
            chat->valid = false;
        g_async_queue_push(chat->queue, data);
        mx_handle_request(chat);
    }
    printf("Closed receiver\n");
    return NULL;
}
