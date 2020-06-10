#include "server.h"

t_dtp *mx_upd_room_desc_request(char *room_name, char *desc) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_ROOM_DESC))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "room_name", MX_J_STR(room_name)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", MX_J_STR(desc)))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_upd_room_desc_handler(t_dtp *desc, t_client *client) { //TODO
    cJSON *token = cJSON_GetObjectItemCaseSensitive(desc->json, "token");
    cJSON *room_name = cJSON_GetObjectItemCaseSensitive(desc->json, "room_name");
    cJSON *desc_str = cJSON_GetObjectItemCaseSensitive(desc->json, "desc");

    if (!token || !cJSON_IsString(token)
        || !mx_isvalid_token(token->valuestring)
        || strcmp(token->valuestring, client->user->token)) {
        return false;
    }
    if (!room_name || !cJSON_IsString(room_name))
        return false;
    if (!desc_str || !cJSON_IsString(desc_str))
        return false;
    return true;
}
