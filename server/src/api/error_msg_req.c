#include "server.h"

t_dtp *mx_error_msg_request(int error_code, char *msg) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_ERROR_MSG))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "error_code", error_code))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "msg", MX_J_STR(msg)))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_error_req_msg_handle(t_dtp *data, t_chat *chat) {
    data++;
    chat++;
    return true;
}
