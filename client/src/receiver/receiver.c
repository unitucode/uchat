#include "client.h"

/*
 * Function: mx_handle_request
 * -------------------------------
 * Handels request from server
 * 
 * request: received string from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_handle_request(char *request, t_chat *chat) {
    t_dtp *data = mx_request_creation(request);

    if (data) {
        if (chat->auth_token
            || data->type == RQ_ERROR_MSG
            || data->type == RQ_TOKEN) {
            if (!chat->request_handler[data->type]
                || !chat->request_handler[data->type](data, chat)) {
                return FALSE;
            }
        }
        else {
            return FALSE;
        }
        mx_free_request(&data);
        return TRUE;
    }
    return FALSE;
}

static gboolean is_connected(t_chat *chat, GDataInputStream *in) {
    if (!g_socket_connection_is_connected(chat->conn)
        || g_output_stream_is_closed(G_OUTPUT_STREAM(chat->out))
        || g_input_stream_is_closed(G_INPUT_STREAM(in))) {
        return FALSE;
    }
    return TRUE;
}

/*
 * Function: mx_receiver
 * -------------------------------
 * Receives requests from server
 * 
 * source_object: the object the asynchronous operation was started with
 * res: GAsyncResult
 * user_data: chat information
 */
void mx_receiver(GObject *source_object, GAsyncResult *res,
                 gpointer user_data) {
    GDataInputStream *in = G_DATA_INPUT_STREAM(source_object);
    gsize count = 0;
    t_chat *chat = (t_chat*)user_data;
    gchar *msg = NULL;

    if (!is_connected(chat, in))
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_ERROR, "disconnected");
    msg = g_data_input_stream_read_line_finish(in, res, &count, NULL);
    #ifndef MX_UNIT_TEST
    if (!msg)
    #endif
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_ERROR, "disconnected");
    if (!mx_handle_request(msg, chat)) {
        g_free(msg);
        g_io_stream_close(G_IO_STREAM(chat->conn), NULL, NULL);
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_ERROR, "disconnected");
    }
    g_free(msg);
    g_data_input_stream_read_line_async(in, G_PRIORITY_DEFAULT, NULL,
                                        mx_receiver, chat);
}
