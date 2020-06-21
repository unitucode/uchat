#include "client.h"

t_dtp *mx_member_info_request(int user_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_MEMBER_INFO))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "user_id", user_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_member_info_handler(t_dtp *data, t_chat *chat) {
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(data->json, "desc");
    cJSON *login = cJSON_GetObjectItemCaseSensitive(data->json, "login");

    if (!cJSON_IsString(desc))
        return false;
    if (!cJSON_IsString(login))
        return false;
    g_print("user desc = %s\n, user login = %s\n", desc->valuestring, login->valuestring);
    (void)chat;
    return true;
}
