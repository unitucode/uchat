#include "api.h"

/*
 * Function: mx_token_request
 * -------------------------------
 * Creates request "token SHA-256 + login"
 * 
 * token: SHA-256 hash + login
 * login: login of user
 * 
 * returns: new request
 */
t_dtp *mx_token_request(char *token, char *login, char *desc) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_TOKEN))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "token", MX_J_STR(token)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "login", MX_J_STR(login)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", MX_J_STR(desc)))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_log_in_token_handler
 * -------------------------------
 * Handles request from client
 * 
 * room: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_log_in_token_handler(t_dtp *token, t_client *client) {
    cJSON *user_token = cJSON_GetObjectItemCaseSensitive(token->json,
                                                         "token");
    t_dtp *reconnect = NULL;

    if (cJSON_IsString(user_token)
        && mx_isvalid_token(user_token->valuestring)) {
        client->user = mx_get_user_by_token(client->info->database,
                                            user_token->valuestring);
    }
    if (!client->user) {
        mx_logger(MX_LOG_FILE, LOGWAR, "Inccorect token\n");
        return FALSE;
    }
    mx_logger(MX_LOG_FILE, LOGMSG, "Logged by token %s\n",
              client->user->login);
    reconnect = mx_reconnect_request(client->user->token,
                                     client->user->login);
    mx_send(client->out, reconnect);
    mx_free_request(&reconnect);
    return TRUE;
}
