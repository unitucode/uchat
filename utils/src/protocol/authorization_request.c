#include "protocol.h"

t_dtp *mx_log_in_request(char *login, char *pass) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", MX_LOG_IN))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "login", MX_J_STR(login)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "pass", MX_J_STR(pass)))
        return NULL;
    return mx_get_transport_data(json_result);
}

t_dtp *mx_sign_up_request(char *login, char *pass) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", MX_SIGN_UP))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "login", MX_J_STR(login)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "pass", MX_J_STR(pass)))
        return NULL;
    return mx_get_transport_data(json_result);
}

t_dtp *mx_token_request(char *token) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", MX_TOKEN))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "token", MX_J_STR(token)))
        return NULL;
    return mx_get_transport_data(json_result);
}
