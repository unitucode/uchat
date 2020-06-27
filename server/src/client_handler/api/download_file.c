#include "api.h"

t_dtp *mx_size_request(goffset size, gchar *name) {
    cJSON *result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(result, "type", RQ_DOWNLOAD_FILE))
        return NULL;
    if (!cJSON_AddNumberToObject(result, "size", size))
        return NULL;
    if (!cJSON_AddStringToObject(result, "name", name))
        return NULL;
    return mx_get_transport_data(result);
}

static void download(t_client *client, GFile *file, gsize size) {
    GOutputStream *out = g_io_stream_get_output_stream(G_IO_STREAM(client->conn));
    gchar *contents = NULL;
    gsize bytes = 0;

    g_file_load_contents(file, NULL, &contents, &bytes, NULL, NULL);
    g_output_stream_write(out, contents, size, NULL, NULL);
    g_free(contents);
    g_io_stream_close(G_IO_STREAM(client->conn), NULL, NULL); // unrefs
}

static void download_file(gchar *msg, t_client *client) {
    GFile *file = g_file_new_for_path(msg);
    GFileInfo *info = g_file_query_info(file, "standard::size,standard::name",
                                        G_FILE_QUERY_INFO_NONE, NULL, NULL);
    t_dtp *size = NULL;

    if (g_file_query_exists(file, NULL)) {
        size = mx_size_request(g_file_info_get_size(info), msg);
        mx_send(client->out, size);
        mx_free_request(&size);
        download(client, file, g_file_info_get_size(info));
    }
    g_free(msg);
}

bool mx_download_file_handler(t_dtp *data, t_client *client) {
    cJSON *token = cJSON_GetObjectItemCaseSensitive(data->json, "token");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *msg_id = cJSON_GetObjectItemCaseSensitive(data->json, "msg_id");

    if (!cJSON_IsString(token) || !cJSON_IsNumber(room_id))
        return false;
    if (!cJSON_IsNumber(msg_id))
        return false;
    client->user = mx_get_user_by_token(client->info->database, token->valuestring); // LEAKS
    if (!mx_is_member(client->info->database, client->user->user_id, room_id->valueint))
        return false;
    if (mx_get_type_member(client->info->database, client->user->user_id, room_id->valueint) == DB_BANNED)
        return false;
    download_file(
        mx_get_text_message_by_id(client->info->database, msg_id->valueint),
        client);
    mx_free_user(&client->user);
    return true;
}
