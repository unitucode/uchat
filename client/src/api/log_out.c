#include "client.h"

t_dtp *mx_log_out_request(char *token) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_LOG_OUT))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "token", MX_J_STR(token)))
        return NULL;
    return mx_get_transport_data(json_result);
}

gboolean mx_log_out_handler(t_dtp *token, t_chat *chat) {
    cJSON *tok = cJSON_GetObjectItemCaseSensitive(token->json, "token");

    if (!cJSON_IsString(tok) || !mx_isvalid_token(tok->valuestring))
        return FALSE;
    if (g_strcmp0(chat->auth_token, tok->valuestring))
        return FALSE;
    mx_free((void**)&chat->auth_token);
    mx_free((void**)&chat->login);
    mx_logout_client(chat);
    return TRUE;
}
