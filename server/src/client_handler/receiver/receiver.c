#include "server.h"

void mx_init_receiver(t_chat *chat) {
    chat->request_handler[RQ_SIGN_UP] = mx_sign_up_handler;
    chat->request_handler[RQ_TOKEN] = mx_log_in_token_handler;
    chat->request_handler[RQ_LOG_IN] = mx_log_in_handler;
    chat->request_handler[RQ_NEW_ROOM] = mx_new_room_handler;
    chat->request_handler[RQ_MSG] = mx_msg_handler;
    chat->request_handler[RQ_GET_ROOMS] = mx_get_rooms_handler;
    chat->request_handler[RQ_LOG_OUT] = mx_log_out_handler;
    chat->request_handler[RQ_GET_NEW_MSGS] = mx_get_msgs_handler;
    chat->request_handler[RQ_UPD_ROOM_DESC] = mx_upd_room_desc_handler;
    chat->request_handler[RQ_UPD_ROOM_NAME] = mx_upd_room_name_handler;
    chat->request_handler[RQ_UPD_USER_DESC] = mx_upd_user_desc_handler;
}

void *mx_receiver(void *arg) {
    t_client *client = (t_client*)arg;
    t_dtp *data = NULL;
    // system("leaks -q uchat_server");

    while ((data = mx_recv(client->ssl))) {
        printf("recv = %s\n", cJSON_Print(data->json));
        if (client->user || data->type == RQ_LOG_IN
            || data->type == RQ_SIGN_UP
            || data->type == RQ_TOKEN) {
            if (!client->chat->request_handler[data->type]
                || !client->chat->request_handler[data->type](data, client)) {
                    break;
            }
        }
        else
            break;
        // send_to_all(client->chat->clients, client->chat, client, dtp->str);
        mx_free_request(&data);
        usleep(MX_DELAY);
    }
    mx_free_request(&data);
    mx_disconnect_client(client);
    printf("Closed receiver Server\n===============================\n");
    system("leaks -q uchat");
    return NULL;
}
