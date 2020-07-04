#include "api.h"

/*
 * Function: mx_init_room_handlers
 * -------------------------------
 * Sets room handlers
 * 
 * chat: information
 */
static void mx_init_room_handlers(t_info *chat) {
    chat->request_handler[RQ_OLD_MSGS] = mx_old_msgs_handler;
    chat->request_handler[RQ_GET_ROOMS] = mx_get_rooms_handler;
    chat->request_handler[RQ_NEW_ROOM] = mx_new_room_handler;
    chat->request_handler[RQ_DEL_ROOM] = mx_del_room_handler;
    chat->request_handler[RQ_JOIN_ROOM] = mx_join_room_handler;
    chat->request_handler[RQ_UPD_ROOM_DESC] = mx_upd_room_desc_handler;
    chat->request_handler[RQ_UPD_ROOM_NAME] = mx_upd_room_name_handler;
    chat->request_handler[RQ_UPD_ROOM_POWR] = NULL;
    chat->request_handler[RQ_SEARCH_CH] = mx_search_rooms_handler;
    chat->request_handler[RQ_GET_MEMBERS] = mx_get_members_handler;
    chat->request_handler[RQ_MEMBER_INFO] = mx_member_info_handler;
    chat->request_handler[RQ_NEW_MEMBER] = NULL;
    chat->request_handler[RQ_BAN_MEMBER] = mx_ban_member_handler;
    chat->request_handler[RQ_UPD_USER_DESC] = mx_upd_user_desc_handler;
    chat->request_handler[RQ_UPLOAD_FILE] = mx_upload_file_handler;
    chat->request_handler[RQ_DOWNLOAD_FILE] = mx_download_file_handler;
    chat->request_handler[RQ_LOG_OUT] = mx_log_out_handler;
    chat->request_handler[RQ_READY_READ] = NULL;
}

/*
 * Function: mx_init_receiver
 * -------------------------------
 * Sets all handlers to requests
 * 
 * chat: information
 */
void mx_init_receiver(t_info *chat) {
    chat->request_handler[RQ_LOG_IN] = mx_log_in_handler;
    chat->request_handler[RQ_SIGN_UP] = mx_sign_up_handler;
    chat->request_handler[RQ_TOKEN] = NULL;
    chat->request_handler[RQ_MSG] = mx_msg_handler;
    chat->request_handler[RQ_EDIT_MSG] = mx_edit_msg_handler;
    chat->request_handler[RQ_DEL_MSG] = mx_del_msg_handler;
    chat->request_handler[RQ_DEL_HIST] = mx_del_hist_handler;
    chat->request_handler[RQ_GET_NEW_MSGS] = mx_get_msgs_handler;
    chat->request_handler[RQ_SEARCH_MSG] = mx_search_msgs_handler;
    chat->request_handler[RQ_ERROR_MSG] = NULL;
    mx_init_room_handlers(chat);
}

gboolean mx_handle_message(t_client *client) {
    if (client->upload_file)
        return FALSE;
    if (!client->msg) {
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_MESSAGE, "[1]closed receiver");
        mx_deinit_client(&client);
        return FALSE;
    }
    if (!mx_handle_request(client->msg, client)) {
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_MESSAGE, "[2]closed receiver");
        mx_deinit_client(&client);
        return FALSE;
    }
    return TRUE;
}

/*
 * Function: mx_handle_request
 * -------------------------------
 * Handles request from client
 * 
 * request: request string
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_handle_request(char *request, t_client *client) {
    t_dtp *data = mx_request_creation(request);

    if (data) {
        if (client->user || data->type == RQ_LOG_IN
            || data->type == RQ_SIGN_UP
            || data->type == RQ_TOKEN
            || data->type == RQ_UPLOAD_FILE
            || data->type == RQ_DOWNLOAD_FILE) {
            if (!client->info->request_handler[data->type]
                || !client->info->request_handler[data->type](data, client)) {
                    return FALSE;
            }
        }
        else
            return FALSE;
        mx_free_request(&data);
        g_usleep(MX_DELAY);
    }
    return TRUE;
}
