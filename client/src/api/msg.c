#include "client.h"

t_dtp *mx_msg_request(char *msg, char *room_name) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_MSG))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "room_name", MX_J_STR(room_name)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "msg", MX_J_STR(msg)))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_msg(t_dtp *data, t_chat *chat) { // TODO
    t_gmsg *gmsg = mx_create_gmsg(data->json);

    if (!gmsg)
        return false;
    chat++;
    return true;
}
