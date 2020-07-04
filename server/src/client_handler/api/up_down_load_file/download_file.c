#include "api.h"

/*
 * Function: mx_size_request
 * -------------------------------
 * Creates request size request that contains size and name of file
 * 
 * size: size of file
 * name: name of file
 * 
 * returns: new request
 */
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

static void download(t_client *client, GFile *file, GDataInputStream *in_d) {
    GOutputStream *out = g_io_stream_get_output_stream(
        G_IO_STREAM(client->conn));
    GFileInputStream *in = g_file_read(file, NULL, NULL);
    gchar *ready = g_data_input_stream_read_line(in_d, NULL, NULL, NULL);
    t_dtp *dtp = mx_request_creation(ready);

    if (dtp && dtp->type == RQ_READY_READ) {
        g_output_stream_splice(
            out, G_INPUT_STREAM(in), G_OUTPUT_STREAM_SPLICE_CLOSE_SOURCE, 
            NULL, NULL);
    }
    if (ready)
        g_free(ready);
    if (dtp)
        mx_free_request(&dtp);
    g_io_stream_close(G_IO_STREAM(client->conn), NULL, NULL);
}

static void download_file(gchar *msg, t_client *client) {
    GFile *file = NULL;
    GFileInfo *info = NULL;
    t_dtp *size = NULL;

    if (!msg)
        return;
    file = g_file_new_for_path(msg);
    info = g_file_query_info(file, "standard::size,standard::name",
                                        G_FILE_QUERY_INFO_NONE, NULL, NULL);
    if (msg && g_file_query_exists(file, NULL)) {
        size = mx_size_request(g_file_info_get_size(info), msg);
        mx_send(client->out, size);
        mx_free_request(&size);
        download(client, file, client->in);
    }
    else
        g_io_stream_close(G_IO_STREAM(client->conn), NULL, NULL);
    g_object_unref(file);
    g_free(msg);
}

static gboolean is_valid(t_client *client, guint64 room_id) {
    if (!mx_is_member(client->info->database, client->user->user_id,
                      room_id)) {
        return FALSE;
    }
    if (mx_get_type_member(client->info->database, client->user->user_id,
                           room_id) == DB_BANNED) {
        return FALSE;
    }
    return TRUE;
}

/*
 * Function: mx_download_file_handler
 * -------------------------------
 * Handles request from client
 * 
 * data: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_download_file_handler(t_dtp *data, t_client *client) {
    cJSON *token = cJSON_GetObjectItemCaseSensitive(data->json, "token");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *msg_id = cJSON_GetObjectItemCaseSensitive(data->json, "msg_id");

    client->is_file = TRUE;
    if (!cJSON_IsNumber(msg_id) || !cJSON_IsNumber(room_id)
        || !cJSON_IsString(token)) {
        return FALSE;
    }
    client->user = mx_get_user_by_token(client->info->database,
                                        token->valuestring);
    if (client->user && !is_valid(client, room_id->valuedouble)) {
        mx_free_user(&client->user);
        return FALSE;
    }
    download_file(
        mx_get_text_message_by_id(client->info->database,
                                  msg_id->valuedouble), client);
    mx_free_user(&client->user);
    return TRUE;
}
