#include "api.h"

/*
 * Function: mx_token_request
 * -------------------------------
 * Creates request "log out"
 * 
 * token: SHA-256 hash + login
 * 
 * returns: new request
 */
t_dtp *mx_log_out_request(char *token) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_LOG_OUT))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "token", MX_J_STR(token)))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_log_out_handler
 * -------------------------------
 * Handles request from client
 * 
 * token: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_log_out_handler(t_dtp *token, t_client *client) {
    cJSON *tok = cJSON_GetObjectItemCaseSensitive(token->json, "token");
    t_dtp *answer = NULL;

    if (!cJSON_IsString(tok) || !mx_isvalid_token(tok->valuestring))
        return FALSE;
    if (strcmp(client->user->token, tok->valuestring))
        return FALSE;
    answer = mx_log_out_request((char*)client->user->token);
    mx_send(client->out, answer);
    g_hash_table_remove(client->info->users, client->user->login);
    mx_free_user(&client->user);
    mx_free_request(&answer);
    return TRUE;
}
