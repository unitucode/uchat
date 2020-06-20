#include "client.h"

t_dtp *mx_token_request(char *token) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_TOKEN))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "token", MX_J_STR(token)))
        return NULL;
    return mx_get_transport_data(json_result);
}

t_dtp *mx_log_in_request(char *login, char *pass) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_LOG_IN))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "login", MX_J_STR(login)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "pass", MX_J_STR(pass)))
        return NULL;
    return mx_get_transport_data(json_result);
}

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

bool mx_authorization_handler(t_dtp *token, t_chat *chat) {
    cJSON *auth_token = NULL;
    cJSON *login = NULL;

    if (chat->auth_token) {
        return false;
    }
    auth_token = cJSON_GetObjectItemCaseSensitive(token->json, "token");
    if (!auth_token || !cJSON_IsString(auth_token)
        || !mx_isvalid_token(auth_token->valuestring)) {
        return false;
    }
    login = cJSON_GetObjectItemCaseSensitive(token->json, "login");
    if (!login || !cJSON_IsString(login)
        || !mx_match_search(login->valuestring, MX_LOGIN_REGEX)) {
        return false;
    }
    chat->login = strdup(login->valuestring);
    chat->auth_token = strdup(auth_token->valuestring);
    mx_get_data(chat);
    mx_start_main_window(chat);
    return true;
}
