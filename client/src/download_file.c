#include "client.h"

t_dtp *mx_download_file_request(guint64 room_id, guint64 msg_id, gchar *token) {
    cJSON *res = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(res, "type", RQ_DOWNLOAD_FILE))
        return NULL;
    if (!cJSON_AddNumberToObject(res, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(res, "msg_id", msg_id))
        return NULL;
    if (!cJSON_AddStringToObject(res, "token", token))
        return NULL;
    return mx_get_transport_data(res);
}

static void prepare_file(t_dtp *request, GSocketConnection *conn) {
    GOutputStream *out = g_io_stream_get_output_stream(G_IO_STREAM(conn));
    GDataOutputStream *out_d = g_data_output_stream_new(out);

    mx_send(out_d, request);
    mx_free_request(&request);
}

static void file_read(gsize size, gchar *name, GInputStream *in) {
    g_print("name = %s\n", name);
    gchar *basename = g_path_get_basename(name);
    gchar *filename = g_strjoin("", MX_FILES_DIR, basename, NULL);
    GFile *file = g_file_new_for_path(filename);
    g_free(filename);
    GFileOutputStream *out = g_file_create(file, G_FILE_CREATE_NONE, NULL, NULL);
    char buf[MX_BUF_FILE + 1];
    gssize read = 0;
    gsize bytes = 0;
    //SET NEW NAME IF EXISTS
    if (size <= MX_MAX_FILE_SIZE) {
        while ((read = g_input_stream_read(in, buf, size, NULL, NULL)) > 0) {
            bytes += read;
            if (bytes > size)
                break;
            if (g_output_stream_write(G_OUTPUT_STREAM(out), buf, read, NULL, NULL) < 0)
                break;
        }
        if (bytes != size) {
            g_file_delete(file, NULL, NULL);
            g_print("bytes = %ld size = %ld\n", bytes, size);
            return;
        }
    }
    if (g_file_query_file_type(file, G_FILE_QUERY_INFO_NONE, NULL) != G_FILE_TYPE_REGULAR) {
        g_file_delete(file, NULL, NULL);
        g_print("not regular");
        return;
    }
}

static void file_ready(GObject *source_object, GAsyncResult *res,
                       gpointer user_data) {
    GInputStream *in_s = g_io_stream_get_input_stream(G_IO_STREAM(user_data));
    gchar *msg = g_data_input_stream_read_line_finish(G_DATA_INPUT_STREAM(source_object), res, NULL, NULL);
    cJSON *answer = cJSON_Parse(msg);
    cJSON *size = NULL;
    cJSON *name = NULL;

    if (!answer)
        return;
    size = cJSON_GetObjectItemCaseSensitive(answer, "size");
    name = cJSON_GetObjectItemCaseSensitive(answer, "name");
    if (!cJSON_IsNumber(size) || !cJSON_IsString(name)) {
        cJSON_Delete(answer);
        return;
    }
    file_read(size->valuedouble, name->valuestring, in_s);
}

void mx_download_file(guint64 room_id, guint64 msg_id, t_chat *chat) {
    GSocketConnection *conn = g_socket_client_connect_to_host(
        chat->cli_conn, chat->argv[1],
        g_ascii_strtoll(chat->argv[2], NULL, 10), NULL, NULL);
    GInputStream *in_s = g_io_stream_get_input_stream(G_IO_STREAM(conn));
    GDataInputStream *in = g_data_input_stream_new(in_s);
    t_dtp *file = mx_download_file_request(room_id, msg_id, chat->auth_token);

    prepare_file(file, conn);
    g_data_input_stream_read_line_async(in, G_PRIORITY_DEFAULT, NULL, file_ready, conn);
}
