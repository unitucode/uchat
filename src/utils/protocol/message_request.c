#include "protocol.h"

t_dtp *mx_msg_request(int id_room, char *from, char *msg) {
    t_dtp *dtp = NULL;
    cJSON *json_result = cJSON_CreateObject();
    char *json_str = NULL;

    if (!cJSON_AddNumberToObject(json_result, "type", MX_MSG))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "id_room", id_room))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "login", MX_J_STR(from)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "msg", MX_J_STR(msg)))
        return NULL;
    json_str = cJSON_Print(json_result);
    dtp = mx_request_creation(json_str);
    mx_free((void**)&json_str);
    cJSON_Delete(json_result);
    return dtp;
}
