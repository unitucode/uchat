#include "client.h"

t_dtp *mx_del_msg_request(int room_id, int msg_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_DEL_MSG))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "msg_id", msg_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_del_msg_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *msg_id = cJSON_GetObjectItemCaseSensitive(data->json, "msg_id");

    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    if (!msg_id || !cJSON_IsNumber(msg_id))
        return false;
    mx_gdel_msg(msg_id->valueint, room_id->valueint, chat->builder);
    return true;
}
