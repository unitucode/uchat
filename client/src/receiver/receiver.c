#include "client.h"

void mx_init_errors(t_chat *chat) {
    chat->error_handler[ER_AUTH_DATA] = mx_err_auth_data_handler;
    chat->error_handler[ER_USER_EXST] = mx_err_user_exist_handler;
}

void mx_init_room_handlers(t_chat *chat) {
    chat->request_handler[RQ_NEW_MEMBER] = mx_new_member_handler;
    chat->request_handler[RQ_BAN_MEMBER] = mx_ban_member_handler;
    chat->request_handler[RQ_GET_ROOMS] = mx_rooms_hanlder;
    chat->request_handler[RQ_NEW_ROOM] = mx_new_room_handler;
    chat->request_handler[RQ_UPD_ROOM_DESC] = mx_upd_room_desc_handler;
    chat->request_handler[RQ_UPD_ROOM_NAME] = mx_upd_room_name_handler;
    chat->request_handler[RQ_GET_NEW_MSGS] = mx_new_msgs_hanlder;
    chat->request_handler[RQ_DEL_ROOM] = mx_del_room_handler;
    chat->request_handler[RQ_SEARCH_CH] = mx_search_rooms_handler;
    chat->request_handler[RQ_JOIN_ROOM] = mx_join_room_handler;
    chat->request_handler[RQ_GET_MEMBERS] = mx_get_members_handler;
    chat->request_handler[RQ_DEL_HIST] = mx_del_hist_handler;
}

void mx_init_handlers(t_chat *chat) {
    chat->request_handler[RQ_TOKEN] = mx_authorization_handler;
    chat->request_handler[RQ_ERROR_MSG] = mx_error_handler;
    chat->request_handler[RQ_LOG_IN] = NULL;
    chat->request_handler[RQ_SIGN_UP] = NULL;
    chat->request_handler[RQ_MSG] = mx_msg_handler;
    chat->request_handler[RQ_LOG_OUT] = mx_log_out_handler;
    chat->request_handler[RQ_UPD_USER_DESC] = mx_upd_user_desc_handler;
    chat->request_handler[RQ_EDIT_MSG] = mx_edit_msg_handler;
    chat->request_handler[RQ_DEL_MSG] = mx_del_msg_handler;
    chat->request_handler[RQ_MEMBER_INFO] = mx_member_info_handler;
    chat->request_handler[RQ_SEARCH_MSG] = mx_search_msgs_handler;
    chat->request_handler[RQ_OLD_MSGS] = mx_old_msgs_hanlder;
    mx_init_room_handlers(chat);
}

bool mx_handle_request(char *request, t_chat *chat) {
    t_dtp *data = mx_request_creation(request);

    if (data) {
        g_print("recv = %s\n", cJSON_Print(data->json));
        if (chat->auth_token
            || data->type == RQ_ERROR_MSG
            || data->type == RQ_TOKEN) {
            if (!chat->request_handler[data->type]
                || !chat->request_handler[data->type](data, chat)) {
                return false;
            }
        }
        else {
            return false;
        }
        mx_free_request(&data);
    }
    return true;
}

void mx_receiver(GObject *source_object, GAsyncResult *res, gpointer user_data) {
    GDataInputStream *in = G_DATA_INPUT_STREAM(source_object);
    GError *error = NULL;
    gsize count = 0;
    t_chat *chat = (t_chat*)user_data;
    gchar *msg = NULL;

    if (!g_socket_connection_is_connected(chat->conn)
        || g_output_stream_is_closed(G_OUTPUT_STREAM(chat->out))
        || g_input_stream_is_closed(G_INPUT_STREAM(in))) {
        return;
    }
    msg = g_data_input_stream_read_line_finish(in, res, &count, &error);
    if (!msg)
        return;
    if (error) {
        g_error ("%s\n", error->message);
        g_clear_error (&error);
    }
    if (!mx_handle_request(msg, chat)) {
        g_free(msg);
        g_io_stream_close(G_IO_STREAM(chat->conn), NULL, NULL);
        return;
    }
    g_free(msg);
    g_data_input_stream_read_line_async(in, G_PRIORITY_DEFAULT, NULL, mx_receiver, chat);
}
