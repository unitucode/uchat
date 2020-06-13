#include "client.h"

t_dtp *mx_del_room_request(int room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_DEL_ROOM))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_del_room_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");

    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    mx_gdel_room(room_id->valueint, chat->builder);
    return true;
}
