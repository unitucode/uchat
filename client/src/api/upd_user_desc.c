#include "client.h"

t_dtp *mx_upd_user_desc_request(char *desc) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_USER_DESC))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", MX_J_STR(desc)))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_upd_user_desc_handler(t_dtp *data, t_chat *chat) {
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(data->json, "desc");
    cJSON *login = cJSON_GetObjectItemCaseSensitive(data->json, "name");

    if (!desc || !cJSON_IsString(desc))
        return false;
    if (!login || !cJSON_IsString(login))
        return false;
    //WORKING WITH GUI
    chat++;
    printf("new desc = %s in %s user\n", desc->valuestring, login->valuestring);
    //WORKING WITH GUI
    return true;
}
