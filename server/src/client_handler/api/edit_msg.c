#include "server.h"

t_dtp *mx_edit_msg_request(char *msg, int room_id, int msg_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_EDIT_MSG))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "msg_id", msg_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "msg", msg))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_edit_msg_handler(t_dtp *msg, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(msg->json, "room_id");
    cJSON *msg_id = cJSON_GetObjectItemCaseSensitive(msg->json, "msg_id");
    cJSON *msg_str = cJSON_GetObjectItemCaseSensitive(msg->json, "msg");

    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    if (!msg_id || !cJSON_IsNumber(msg_id))
        return false;
    if (!msg_str || !cJSON_IsNumber(msg_str))
        return false;
    //TODO
    client++;
    //TODO
    return true;
}
