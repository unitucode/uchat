#include "api.h"

static void resend_file(t_client *client, gchar *filename, guint64 room_id,
                        guint64 size) {
    t_dtp *file_request = NULL;
    cJSON *msg = cJSON_CreateObject();
    t_db_message *db_msg = NULL;

    cJSON_AddNumberToObject(msg, "room_id", room_id);
    cJSON_AddStringToObject(msg, "message", filename);
    cJSON_AddNumberToObject(msg, "msg_type", DB_FILE_MSG);
    db_msg = mx_parse_message(msg);
    db_msg->user_id = client->user->user_id;
    db_msg->power = size;
    mx_insert_message(client->info->database, db_msg);
    mx_update_room_power(client, room_id);
    file_request = mx_msg_request(db_msg);
    mx_free_message(&db_msg);
    cJSON_Delete(msg);
    mx_send_to_all(file_request, client, room_id);
    mx_free_request(&file_request);
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

static gpointer upload_file_thread(gpointer data) {
    t_file_helper *file = (t_file_helper*)data;
    gchar *filename = g_strdup_printf(
        "%s%"G_GUINT64_FORMAT"%s%s%s", MX_FILES_DIR,
        mx_get_time(DB_MICROSECOND), file->client->user->login, MX_FILE_DELIM,
        file->name);

    if (mx_read_file(file->client, file->size, filename)) {
        resend_file(file->client, filename, file->room_id, file->size);
    }
    g_io_stream_close(G_IO_STREAM(file->client->conn), NULL, NULL);
    file->client->upload_file = FALSE;
    g_free(filename);
    g_free(file->name);
    g_free(file);
    g_thread_exit(NULL);
    return NULL;
}

static gboolean create_file(t_client *client, guint64 size, guint64 room_id,
                            gchar *name) {
    t_file_helper *file = g_malloc0(sizeof(t_file_helper));

    file->size = size;
    file->room_id = room_id;
    file->client = client;
    file->name = g_strdup(name);
    client->upload_file = TRUE;
    g_thread_new("upload_thread", upload_file_thread, file);
    return TRUE;
}

/*
 * Function: mx_upload_file_handler
 * -------------------------------
 * Handles request from client
 * 
 * data: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_upload_file_handler(t_dtp *data, t_client *client) {
    cJSON *size = cJSON_GetObjectItemCaseSensitive(data->json, "size");
    cJSON *name = cJSON_GetObjectItemCaseSensitive(data->json, "name");
    cJSON *token = cJSON_GetObjectItemCaseSensitive(data->json, "token");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");

    client->is_file = TRUE;
    if (!cJSON_IsNumber(size) || !cJSON_IsString(name))
        return FALSE;
    if (!cJSON_IsString(token) || !cJSON_IsNumber(room_id))
        return FALSE;
    client->user = mx_get_user_by_token(client->info->database,
                                        token->valuestring);
    if (!is_valid(client, room_id->valuedouble))
        return FALSE;
    if (!create_file(client, size->valuedouble, room_id->valuedouble,
                     name->valuestring)) {
        return FALSE;
    }
    return TRUE;
}
