#include "client.h"

t_dtp *mx_member_info_request(int user_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_MEMBER_INFO))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "user_id", user_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

gboolean mx_member_info_handler(t_dtp *data, t_chat *chat) {
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(data->json, "desc");
    cJSON *login = cJSON_GetObjectItemCaseSensitive(data->json, "login");

    if (!cJSON_IsString(desc))
        return FALSE;
    if (!cJSON_IsString(login))
        return FALSE;
    mx_show_user_info(chat->builder, login->valuestring, desc->valuestring);
    return TRUE;
}
