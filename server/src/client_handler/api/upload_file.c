#include "api.h"

static gboolean read_file(t_client *client, gsize size, char *name) {
    GFile *file = g_file_new_for_path(name);
    GFileOutputStream *out = g_file_create(file, G_FILE_CREATE_NONE,
                                           NULL, NULL);
    char buf[MX_BUF_FILE + 1];
    gssize read = 0;
    gsize bytes = 0;
    //SET NEW NAME IF EXISTS
    if (size <= MX_MAX_FILE_SIZE) {
        while ((read = g_input_stream_read(client->in_s, buf, size, NULL, NULL)) > 0) {
            bytes += read;
            if (bytes > size)
                break;
            if (g_output_stream_write(G_OUTPUT_STREAM(out), buf, read, NULL, NULL) < 0)
                break;
        }
        if (bytes != size) {
            g_file_delete(file, NULL, NULL);
            g_print("bytes = %ld size = %ld\n", bytes, size);
            return FALSE;
        }
    }
    if (g_file_query_file_type(file, G_FILE_QUERY_INFO_NONE, NULL) != G_FILE_TYPE_REGULAR) {
        g_file_delete(file, NULL, NULL);
        g_print("not regular");
        return FALSE;
    }
    return TRUE;
}

static void resend_file(t_client *client, gchar *filename, gint room_id) {
    t_dtp *file_request = NULL;
    cJSON *msg = cJSON_CreateObject();
    t_db_message *db_msg = NULL;

    cJSON_AddNumberToObject(msg, "room_id", room_id);
    cJSON_AddStringToObject(msg, "message", filename);
    cJSON_AddNumberToObject(msg, "msg_type", DB_FILE_MSG);
    db_msg = mx_parse_message(msg);
    db_msg->user_id = client->user->user_id;
    mx_insert_message(client->info->database, db_msg);
    file_request = mx_msg_request(db_msg);
    mx_free_message(&db_msg);
    cJSON_Delete(msg);
    mx_send_to_all(file_request, client, room_id);
    mx_free_request(&file_request);
}

gboolean mx_upload_file_handler(t_dtp *data, t_client *client) {
    cJSON *size = cJSON_GetObjectItemCaseSensitive(data->json, "size");
    cJSON *name = cJSON_GetObjectItemCaseSensitive(data->json, "name");
    cJSON *token = cJSON_GetObjectItemCaseSensitive(data->json, "token");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    gchar *filename = NULL;

    if (!cJSON_IsNumber(size) || !cJSON_IsString(name))
        return FALSE;
    if (!cJSON_IsString(token) || !cJSON_IsNumber(room_id))
        return FALSE;
    client->user = mx_get_user_by_token(client->info->database, token->valuestring);
    if (!mx_is_member(client->info->database, client->user->user_id, room_id->valuedouble))
        return FALSE;
    if (mx_get_type_member(client->info->database, client->user->user_id, room_id->valuedouble) == DB_BANNED)
        return FALSE;
    filename = g_strdup_printf(
        "%s%"G_GUINT64_FORMAT"%s%s", MX_FILES_DIR, mx_get_time(DB_MICROSECOND),
        client->user->login, name->valuestring);
    if (!read_file(client, size->valueint, filename)) {
        g_free(filename);
        return FALSE;
    }
    resend_file(client, filename, room_id->valueint);
    g_io_stream_close(G_IO_STREAM(client->conn), NULL, NULL);
    g_free(filename);
    mx_free_user(&client->user);
    return TRUE;
}
