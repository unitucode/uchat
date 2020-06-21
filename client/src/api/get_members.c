#include "client.h"

t_dtp *mx_get_members_request(int room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_GET_MEMBERS))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_get_members_handler(t_dtp *data, t_chat *chat) {
    cJSON *members = cJSON_GetObjectItemCaseSensitive(data->json, "members");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");

    if (!cJSON_IsArray(members))
        return false;
    if (!cJSON_IsNumber(room_id))
        return false;
    (void)chat;
    return true;
}
