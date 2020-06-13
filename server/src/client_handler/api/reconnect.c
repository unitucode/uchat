#include "server.h"

t_dtp *mx_reconnect_request(char *token, char *login) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_RECONNECT))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "token", MX_J_STR(token)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "login", login))
        return NULL;
    return mx_get_transport_data(json_result);
}
