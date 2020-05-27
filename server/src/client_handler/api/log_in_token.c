#include "server.h"

t_dtp *mx_token_request(char *token) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_TOKEN))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "token", MX_J_STR(token)))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_log_in_token(t_dtp *token, t_client *client) { // TODO!!!!!!
    token++;
    client++;
    return true;
}
