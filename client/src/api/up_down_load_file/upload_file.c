#include "client.h"

static gboolean is_server_ready(GSocketConnection *conn) {
    GInputStream *in = g_io_stream_get_input_stream(G_IO_STREAM(conn));
    GDataInputStream *in_d = g_data_input_stream_new(in);
    gchar *ready = g_data_input_stream_read_line(in_d, NULL, NULL, NULL);
    t_dtp *dtp = mx_request_creation(ready);

    if (dtp && dtp->type == RQ_READY_READ) {
        mx_free_request(&dtp);
        if (ready)
            g_free(ready);
        return TRUE;
    }
    if (ready)
        g_free(ready);
    return FALSE;
}

static void send_file(t_dtp *request, GFile *file, t_chat *chat) {
    GSocketConnection *conn = g_socket_client_connect_to_host(
        chat->cli_conn, chat->argv[1],
        g_ascii_strtoll(chat->argv[2], NULL, 10), NULL, NULL);
    GOutputStream *out = g_io_stream_get_output_stream(G_IO_STREAM(conn));
    GDataOutputStream *d_out = g_data_output_stream_new(G_OUTPUT_STREAM(out));
    GFileInputStream *file_in = g_file_read(file, NULL, NULL);

    mx_send(d_out, request);
    mx_free_request(&request);
    if (is_server_ready(conn)) {
        g_output_stream_splice(out, G_INPUT_STREAM(file_in),
                            G_OUTPUT_STREAM_SPLICE_CLOSE_SOURCE, NULL, NULL);
    }
    g_io_stream_close(G_IO_STREAM(conn), NULL, NULL);
}

/*
 * Function: mx_upload_file
 * -------------------------------
 * Uploads file to server
 * 
 * path: path to file
 * room_id: room id
 * chat: information about chat
 */
void mx_upload_file(gchar *path, gint room_id, t_chat *chat) {
    GFile *file = g_file_new_for_path(path);
    GFileInfo *info = g_file_query_info(file, "standard::size,standard::name",
                                        G_FILE_QUERY_INFO_NONE, NULL, NULL);
    t_dtp *file_request = mx_upload_file_request(
        g_file_info_get_name(info), g_file_info_get_size(info),
        chat->auth_token, room_id);

    if (g_file_info_get_size(info) <= MX_MAX_FILE_SIZE) 
        send_file(file_request, file, chat);
    g_object_unref(info);
}
