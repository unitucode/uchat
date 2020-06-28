#include "client.h"

t_dtp *mx_edit_msg_request(char *msg, int room_id, int msg_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_EDIT_MSG))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "msg_id", msg_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "msg", MX_J_STR(msg)))
        return NULL;
    return mx_get_transport_data(json_result);
}

gboolean mx_edit_msg_handler(t_dtp *data, t_chat *chat) {
    cJSON *msg = cJSON_GetObjectItemCaseSensitive(data->json, "msg");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *msg_id = cJSON_GetObjectItemCaseSensitive(data->json, "msg_id");

    if (!cJSON_IsString(msg))
        return FALSE;
    if (!cJSON_IsNumber(room_id))
        return FALSE;
    if (!cJSON_IsNumber(msg_id))
        return FALSE;
    mx_gupd_msg_text(msg_id->valueint, room_id->valueint,
                     msg->valuestring, chat->builder);
    return TRUE;
}
