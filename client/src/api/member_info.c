#include "client.h"

/*
 * Function: mx_member_info_request
 * -------------------------------
 * Creates member info request
 * 
 * user_id: user id
 * 
 * returns: member info request
 */
t_dtp *mx_member_info_request(guint64 user_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_MEMBER_INFO))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "user_id", user_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_member_info_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_member_info_handler(t_dtp *data, t_chat *chat) {
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(data->json, "desc");
    cJSON *login = cJSON_GetObjectItemCaseSensitive(data->json, "login");

    if (!cJSON_IsString(desc) || !cJSON_IsString(login))
        return FALSE;
    mx_show_user_info(chat->builder, login->valuestring, desc->valuestring);
    return TRUE;
}
