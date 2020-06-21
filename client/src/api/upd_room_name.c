#include "client.h"

t_dtp *mx_upd_room_name_request(int room_id, char *name) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_ROOM_NAME))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "room_name", MX_J_STR(name)))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_upd_room_name_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *room_name = cJSON_GetObjectItemCaseSensitive(data->json, "room_name");

    if (!cJSON_IsNumber(room_id))
        return false;
    if (!cJSON_IsString(room_name))
        return false;
    mx_gupd_room_name(room_id->valueint, room_name->valuestring,
                      chat->builder);
    return true;
}
