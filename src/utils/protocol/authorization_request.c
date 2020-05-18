#include "protocol.h"

t_dtp *mx_log_in_request(char *login, char *pass) {
    t_dtp *dtp = NULL;
    cJSON *json_result = cJSON_CreateObject();
    char *json_str = NULL;

    if (!cJSON_AddNumberToObject(json_result, "type", MX_LOG_IN))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "login", MX_J_STR(login)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "pass", MX_J_STR(pass)))
        return NULL;
    json_str = cJSON_Print(json_result);
    dtp = mx_request_creation(json_str);
    mx_free((void**)&json_str);
    cJSON_Delete(json_result);
    return dtp;
}

t_dtp *mx_sign_up_request(char *login, char *pass) {
    t_dtp *dtp = NULL;
    cJSON *json_result = cJSON_CreateObject();
    char *json_str = NULL;

    if (!cJSON_AddNumberToObject(json_result, "type", MX_SIGN_UP))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "login", MX_J_STR(login)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "pass", MX_J_STR(pass)))
        return NULL;
    json_str = cJSON_Print(json_result);
    dtp = mx_request_creation(json_str);
    mx_free((void**)&json_str);
    cJSON_Delete(json_result);
    return dtp;
}

t_dtp *mx_log_in_token_request(char *token) {
    t_dtp *dtp = NULL;
    cJSON *json_result = cJSON_CreateObject();
    char *json_str = NULL;

    if (!cJSON_AddNumberToObject(json_result, "type", MX_SIGN_UP))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "token", MX_J_STR(token)))
        return NULL;
    json_str = cJSON_Print(json_result);
    dtp = mx_request_creation(json_str);
    mx_free((void**)&json_str);
    cJSON_Delete(json_result);
    return dtp;
}
