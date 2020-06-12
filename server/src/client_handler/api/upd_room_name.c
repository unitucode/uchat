#include "server.h"

t_dtp *mx_log_out_request(char *token) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_LOG_OUT))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "token", token))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_log_out_handler(t_dtp *room, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(room->json, "room_id");
    cJSON *room_name = cJSON_GetObjectItemCaseSensitive(room->json, "room_name");
    t_db_room *room_db = NULL;

    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    if (!room_name || !cJSON_IsString(room_name))
        return false;
    room_db = mx_get_room_by_id(client->chat->database, room_id->valueint);
    if (strcmp(room_db->customer, client->user->login))
        return false;
    mx_update
    mx_free_room(&room_db);
    return true;
}
