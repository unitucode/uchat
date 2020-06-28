#include "client.h"

/*
 * Function: mx_token_request
 * -------------------------------
 * Creates token request
 * 
 * token: SHA-256 hash + login
 * 
 * returns: token request
 */
t_dtp *mx_token_request(char *token) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_TOKEN))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "token", MX_J_STR(token)))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_log_in_request
 * -------------------------------
 * Creates log in request
 * 
 * login: user login
 * pass: SHA-256 hash
 * 
 * returns: log in request
 */
t_dtp *mx_log_in_request(char *login, char *pass) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_LOG_IN))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "login", MX_J_STR(login)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "pass", MX_J_STR(pass)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "name", ""))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", ""))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_sign_up_request
 * -------------------------------
 * Creates sign up request
 * 
 * login: user login
 * pass: SHA-256 hash
 * 
 * returns: sign up request
 */
t_dtp *mx_sign_up_request(char *login, char *pass) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_SIGN_UP))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "login", MX_J_STR(login)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "pass", MX_J_STR(pass)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "name", ""))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", ""))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_authorization_handler
 * -------------------------------
 * Handles request from server
 * 
 * token: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_authorization_handler(t_dtp *token, t_chat *chat) {
    cJSON *auth_token = cJSON_GetObjectItemCaseSensitive(token->json,
                                                         "token");
    cJSON *login = cJSON_GetObjectItemCaseSensitive(token->json, "login");
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(token->json, "desc");

    if (chat->auth_token || !cJSON_IsString(auth_token)
        || !cJSON_IsString(login)
        || !mx_isvalid_token(auth_token->valuestring)
        || !mx_match_search(login->valuestring, MX_LOGIN_REGEX)) {
        return FALSE;
    }
    chat->login = strdup(login->valuestring);
    chat->auth_token = strdup(auth_token->valuestring);
    chat->desc = strdup(desc->valuestring);
    mx_get_data(chat);
    mx_start_main_window(chat);
    return TRUE;
}
