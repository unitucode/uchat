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
