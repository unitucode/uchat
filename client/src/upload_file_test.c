#include "client.h"

// static void write_ready(GObject *source_object, GAsyncResult *res, gpointer user_data) {
//     GError *error = NULL;

//     g_print("wrote %ld\n", g_output_stream_write_finish(G_OUTPUT_STREAM(source_object), res, &error));
//     if (error) {
//         g_printerr("error = %s\n", error->message);
//         g_clear_error(&error);
//     }
//     (void)user_data;
// }

// static void bytes_ready(GObject *source_object, GAsyncResult *res, gpointer user_data) { // ADD ERRORS
//     // GOutputStream *b_out = g_buffered_output_stream_new(chat->out_s);
//     // goffset written = g_bytes_get_size(bytes);
    
//     // // g_output_stream_write_bytes_async(b_out, bytes, G_PRIORITY_DEFAULT, NULL, write_ready, NULL);
//     // while (written > 0) {
//     //     written -= g_output_stream_write_bytes(b_out, bytes, NULL, NULL);
//     //     g_print("written = %lld\n", written);
//     // }
//     // (void)bytes;
//     GFileInfo *info = g_file_query_info(G_FILE(source_object), "standard::size,standard::name", G_FILE_QUERY_INFO_NONE, NULL, NULL);
//     // GBytes *bytes = g_file_load_bytes_finish(G_FILE(source_object), res, NULL, NULL);
//     char *bytes = NULL;
//     gsize length = 0;
//     g_file_load_contents(G_FILE(source_object), NULL, &bytes, &length, NULL, NULL);
//     t_dtp *upload_file = mx_upload_file_request((char*)g_file_info_get_name(info), length);
//     t_chat *chat = (t_chat*)user_data;

//     mx_send(chat->out, upload_file);
//     g_print("sent = %ld\n", g_output_stream_write(chat->out_s, bytes, length, NULL, NULL));
//     // g_print("sent = %ld\n", g_output_stream_write_bytes(chat->out_s, bytes, NULL, NULL));
//     // g_print("written = %ld\n", g_output_stream_write_bytes(chat->out_s, bytes, NULL, NULL));
//     (void)res;
// }

static void file_ready(GObject *source_object, GAsyncResult *res, gpointer user_data) { //ADD ERRORS
    char *contents = NULL;
    gsize length = 0;
    GOutputStream *out = g_io_stream_get_output_stream(G_IO_STREAM(user_data));

    g_file_load_contents_finish(G_FILE(source_object), res, &contents, &length, NULL, NULL);
    g_print("send = %ld\n", g_output_stream_write(out, contents, length, NULL, NULL));
    g_io_stream_close(G_IO_STREAM(user_data), NULL, NULL);
    (void)res;
}

static void mx_send_file(t_dtp *request, GSocketConnection *conn, GFile *file) {
    GOutputStream *out = g_io_stream_get_output_stream(G_IO_STREAM(conn));
    GDataOutputStream *out_data = g_data_output_stream_new(out);

    mx_send(out_data, request);
    g_file_load_contents_async(file, NULL, file_ready, conn);
}

void mx_upload_file(char *path, t_chat *chat) { //TODO ERRORS
    GFile *file = g_file_new_for_path(path);
    GFileInfo *info = g_file_query_info(file, "standard::size,standard::name", G_FILE_QUERY_INFO_NONE, NULL, NULL);
    t_dtp *request = mx_upload_file_request((char*)g_file_info_get_name(info), g_file_info_get_size(info), chat->auth_token);

    GSocketConnection *conn = g_socket_client_connect_to_host(chat->cli_conn, chat->argv[1], g_ascii_strtoll(chat->argv[2], NULL, 10), NULL, NULL);
    mx_send_file(request, conn, file);
}
