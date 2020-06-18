#include "server.h"


// static void bytes_ready(GObject *source_object, GAsyncResult *res, gpointer user_data) {
//     GBytes *bytes = g_input_stream_read_bytes_finish(G_INPUT_STREAM(source_object), res, NULL);
//     GFile *file = g_file_new_for_path("new_file");

//     g_file_replace_contents_bytes_async(file, bytes, NULL, FALSE, G_FILE_CREATE_NONE, NULL, write_ready, NULL);
//     (void)user_data;
// }

// static void write_ready(GObject *source_object, GAsyncResult *res, gpointer user_data) {
//     g_print("read = %d\n", g_file_replace_contents_finish(G_FILE(source_object), res, NULL, NULL));
//     (void)user_data;
// }

void read_file(t_client *client, gsize size, char *name) {
    GFile *file = g_file_new_for_path(name);
    gsize length = 0;
    char buff[size + 1];
    GInputStream *in = g_buffered_input_stream_new(G_INPUT_STREAM(client->in_s));

    bzero(buff, sizeof(buff));
    while (length < size) {
        length += g_input_stream_read(in, buff + length, size, NULL, NULL);
    }
    g_print("buf = %s\n", buff);
    g_file_replace_contents(file, buff, length, NULL, FALSE, G_FILE_CREATE_NONE, NULL, NULL, NULL);
    (void)client;
    (void)size;
}

bool mx_upload_file_handler(t_dtp *data, t_client *client) {
    cJSON *size = cJSON_GetObjectItemCaseSensitive(data->json, "size");
    cJSON *name = cJSON_GetObjectItemCaseSensitive(data->json, "name");

    if (!size || !cJSON_IsNumber(size))
        return false;
    if (!name || !cJSON_IsString(name))
        return false;
    g_print("start_handle\n");
    read_file(client, size->valueint, name->valuestring);
    g_print("end_handle\n");
    return true;
}
