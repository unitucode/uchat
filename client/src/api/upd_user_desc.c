#include "client.h"

/*
 * Function: mx_upd_user_desc_request
 * -------------------------------
 * Creates update user description request
 * 
 * desc: new description
 * 
 * returns: update description user request
 */
t_dtp *mx_upd_user_desc_request(char *desc) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_USER_DESC))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", MX_J_STR(desc)))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_upd_user_desc_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_upd_user_desc_handler(t_dtp *data, t_chat *chat) {
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(data->json, "desc");

    if (!cJSON_IsString(desc))
        return FALSE;
    if (chat->desc)
        g_free(chat->desc);
    chat->desc = g_strdup(desc->valuestring);
    return TRUE;
}
