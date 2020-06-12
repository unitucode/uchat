#include "client.h"

void mx_init_errors(t_chat *chat) {
    chat->error_handler[ER_AUTH_DATA] = mx_err_auth_data_handler;
    chat->error_handler[ER_USER_EXST] = mx_err_user_exist_handler;
}

void mx_init_handlers(t_chat *chat) {
    pthread_t tid;

    chat->request_handler[RQ_TOKEN] = mx_authorization_handler;
    chat->request_handler[RQ_ERROR_MSG] = mx_error_handler;
    chat->request_handler[RQ_LOG_IN] = NULL;
    chat->request_handler[RQ_SIGN_UP] = NULL;
    chat->request_handler[RQ_GET_ROOMS] = mx_rooms_hanlder;
    chat->request_handler[RQ_GET_NEW_MSGS] = mx_new_msgs_hanlder;
    chat->request_handler[RQ_NEW_ROOM] = mx_new_room_handler;
    chat->request_handler[RQ_USERS_ONLINE] = mx_update_users_handler;
    chat->request_handler[RQ_MSG] = mx_msg_handler;
    chat->request_handler[RQ_LOG_OUT] = mx_log_out_handler;
    chat->request_handler[RQ_UPD_ROOM_DESC] = mx_upd_room_desc_handler;
    chat->request_handler[RQ_UPD_ROOM_NAME] = mx_upd_room_name_handler;
    chat->request_handler[RQ_UPD_USER_DESC] = mx_upd_user_desc_handler;
    mx_pthread_create(&tid, NULL, mx_receiver, chat);
}


void *mx_receiver(void *arg) {
    t_chat *chat = (t_chat*)arg;
    t_dtp *data = NULL;

    while (true) {
        while ((data = mx_recv(chat->ssl)) && chat->valid) {
            printf("recv = %s", cJSON_Print(data->json));
            if (g_async_queue_length(chat->queue) > MX_MAX_LENGTH_QUEUE)
                chat->valid = false;
            g_async_queue_push(chat->queue, data);
            mx_handle_request(chat);
        }
        SSL_shutdown(chat->ssl);
        if (!mx_reconnect(chat)) {
            printf("Closed receiver\n");
            break;
        }
    }
    return NULL;
}
