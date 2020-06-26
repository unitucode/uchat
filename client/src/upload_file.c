#include "client.h"

static void file_ready(GObject *source_object, GAsyncResult *res,
                       gpointer user_data) {
    GOutputStream *out = g_io_stream_get_output_stream(
        G_IO_STREAM(user_data));
    char *contents = NULL;
    gsize length = 0;

    g_file_load_contents_finish(
        G_FILE(source_object), res, &contents, &length, NULL, NULL);
    g_output_stream_write(out, contents, length, NULL, NULL);
    g_io_stream_close(G_IO_STREAM(user_data), NULL, NULL);
    g_object_unref(G_FILE(source_object));
}

static void send_file(t_dtp *request, GFile *file, t_chat *chat) {
    GSocketConnection *conn = g_socket_client_connect_to_host(
        chat->cli_conn, chat->argv[1],
        g_ascii_strtoll(chat->argv[2], NULL, 10), NULL, NULL);
    GOutputStream *out = g_io_stream_get_output_stream(G_IO_STREAM(conn));
    GDataOutputStream *d_out = g_data_output_stream_new(G_OUTPUT_STREAM(out));

    mx_send(d_out, request);
    mx_free_request(&request);
    g_file_load_contents_async(file, NULL, file_ready, conn);
}

void mx_upload_file(gchar *path, gint room_id, t_chat *chat) {
    GFile *file = g_file_new_for_path(path);
    GFileInfo *info = g_file_query_info(file, "standard::size,standard::name",
                                        G_FILE_QUERY_INFO_NONE, NULL, NULL);
    t_dtp *file_request = mx_upload_file_request(
        g_file_info_get_name(info), g_file_info_get_size(info),
        chat->auth_token, room_id);

    send_file(file_request, file, chat);
    g_object_unref(info);
}
