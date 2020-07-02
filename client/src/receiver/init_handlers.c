#include "client.h"

void mx_init_errors(t_chat *chat) {
    chat->error_handler[ER_AUTH_DATA] = mx_err_auth_data_handler;
    chat->error_handler[ER_USER_EXST] = mx_err_user_exist_handler;
    chat->error_handler[ER_CLI_EXST] = mx_err_cli_exist_handler;
}

void mx_init_room_handlers(t_chat *chat) {
    chat->request_handler[RQ_DEL_HIST] = mx_del_hist_handler;
    chat->request_handler[RQ_GET_NEW_MSGS] = mx_new_msgs_hanlder;
    chat->request_handler[RQ_GET_ROOMS] = mx_rooms_hanlder;
    chat->request_handler[RQ_NEW_ROOM] = mx_new_room_handler;
    chat->request_handler[RQ_DEL_ROOM] = mx_del_room_handler;
    chat->request_handler[RQ_NEW_MEMBER] = mx_new_member_handler;
    chat->request_handler[RQ_JOIN_ROOM] = mx_join_room_handler;
    chat->request_handler[RQ_UPD_ROOM_NAME] = mx_upd_room_name_handler;
    chat->request_handler[RQ_UPD_ROOM_DESC] = mx_upd_room_desc_handler;
    chat->request_handler[RQ_UPD_ROOM_POWR] = mx_upd_room_power_handler;
    chat->request_handler[RQ_SEARCH_CH] = mx_search_rooms_handler;
    chat->request_handler[RQ_GET_MEMBERS] = mx_get_members_handler;
    chat->request_handler[RQ_BAN_MEMBER] = mx_ban_member_handler;
}

/*
 * Function: mx_init_handlers
 * -------------------------------
 * Initializate chat handlers
 * 
 * chat: information about chat
 */
void mx_init_handlers(t_chat *chat) {
    chat->request_handler[RQ_LOG_IN] = NULL;
    chat->request_handler[RQ_SIGN_UP] = NULL;
    chat->request_handler[RQ_TOKEN] = mx_authorization_handler;
    chat->request_handler[RQ_MSG] = mx_msg_handler;
    chat->request_handler[RQ_EDIT_MSG] = mx_edit_msg_handler;
    chat->request_handler[RQ_DEL_MSG] = mx_del_msg_handler;
    chat->request_handler[RQ_SEARCH_MSG] = mx_search_msgs_handler;
    chat->request_handler[RQ_ERROR_MSG] = mx_error_handler;
    chat->request_handler[RQ_OLD_MSGS] = mx_old_msgs_hanlder;
    chat->request_handler[RQ_MEMBER_INFO] = mx_member_info_handler;
    chat->request_handler[RQ_UPD_USER_DESC] = mx_upd_user_desc_handler;
    chat->request_handler[RQ_LOG_OUT] = mx_log_out_handler;
    chat->request_handler[RQ_UPLOAD_FILE] = NULL;
    chat->request_handler[RQ_DOWNLOAD_FILE] = NULL;
    chat->request_handler[RQ_READY_READ] = NULL;
    mx_init_room_handlers(chat);
}
