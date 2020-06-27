#include "server.h"

t_dtp *mx_size_request(guint64 size) {
    cJSON *result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(result, "type", RQ_DOWNLOAD_FILE))
        return NULL;
    if (!cJSON_AddNumberToObject(result, "size", size))
        return NULL;
    return mx_get_transport_data(result);
}

static void download_file(guint64 room_id, guint64 msg_id, t_db_message *msg) {

}

bool mx_download_file_handler(t_dtp *data, t_client *client) {
    cJSON *token = cJSON_GetObjectItemCaseSensitive(data->json, "token");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *msg_id = cJSON_GetObjectItemCaseSensitive(data->json, "msg_id");
    gchar *filename = NULL;

    if (!cJSON_IsString(token) || !cJSON_IsNumber(room_id))
        return false;
    if (!cJSON_IsNumber(msg_id))
        return false;
    client->user = mx_get_user_by_token(client->info->database, token->valuestring); // LEAKS
    if (!mx_is_member(client->info->database, client->user->user_id, room_id->valueint))
        return false;
    if (mx_get_type_member(client->info->database, client->user->user_id, room_id->valueint) == DB_BANNED)
        return false;
    download_file(room_id->valueint, msg_id->valueint);
    mx_free_user(&client->user);
    return true;
}