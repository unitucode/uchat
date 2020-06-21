#include "server.h"

t_dtp *mx_upd_user_desc_request(char *desc) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_USER_DESC))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", desc))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_upd_user_desc_handler(t_dtp *desc_data, t_client *client) {
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(desc_data->json, "desc");
    t_dtp *resend = NULL;
    
    if (!cJSON_IsString(desc))
        return false;
    mx_edit_desc_user(client->info->database, client->user->user_id, desc->valuestring);
    resend = mx_upd_user_desc_request(desc->valuestring);
    mx_send(client->out, resend);
    mx_free_request(&resend);
    return true;
}
