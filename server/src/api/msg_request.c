#include "server.h"

t_dtp *mx_msg_request(int id_room, char *from, char *msg) {  
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_MSG))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "id_room", id_room))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "login", MX_J_STR(from)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "msg", MX_J_STR(msg)))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_msg_req_handle(t_dtp *data, t_chat *chat) {
    data++;
    chat++;
    return true;
}
