#include "server.h"

t_dtp *mx_upd_room_desc_request(int room_id, char *desc) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_ROOM_DESC))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", desc))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_upd_room_desc_handler(t_dtp *room, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(room->json, "room_id");
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(room->json, "desc");
    t_db_room *room_db = NULL;
    t_dtp *resend = NULL;

    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    if (!desc || !cJSON_IsString(desc))
        return false;
    room_db = mx_get_room_by_id(client->chat->database, room_id->valueint);
    if (!room_db || strcmp(room_db->customer, client->user->login)) {
        mx_free_room(&room_db);
        return false;
    }
    mx_update_description_room_by_id(client->chat->database, room_id->valueint, desc->valuestring);
    resend = mx_upd_room_desc_request(room_id->valueint, desc->valuestring);
    if (resend)
        mx_send_to_all(resend, client);
    mx_free_request(&resend);
    mx_free_room(&room_db);
    return true;
}
