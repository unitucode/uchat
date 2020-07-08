#include "api.h"

/*
 * Function: mx_upd_user_desc_request
 * -------------------------------
 * Creates request "update user desc"
 * 
 * desc: new description
 * 
 * returns: new request
 */
t_dtp *mx_upd_user_desc_request(char *desc) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_USER_DESC))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", desc))
        return NULL;
    return mx_get_transport_data(json_result);
}

static gboolean is_valid(gchar *desc) {
    gsize len = strlen(desc);

    if (len > MX_MAX_MESSAGE)
        return FALSE;
    return TRUE;
}

/*
 * Function: mx_upd_user_desc_handler
 * -------------------------------
 * Handles request from client
 * 
 * desc_data: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_upd_user_desc_handler(t_dtp *desc_data, t_client *client) {
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(desc_data->json, "desc");
    t_dtp *resend = NULL;
    
    if (!cJSON_IsString(desc) || !is_valid(desc->valuestring))
        return FALSE;
    mx_edit_desc_user(client->info->database, client->user->user_id,
                      desc->valuestring);
    resend = mx_upd_user_desc_request(desc->valuestring);
    mx_send(client->out, resend);
    mx_free_request(&resend);
    return TRUE;
}
