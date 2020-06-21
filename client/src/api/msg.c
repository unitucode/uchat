#include "client.h"

t_dtp *mx_msg_request(char *msg, int room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_MSG))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "message", MX_J_STR(msg)))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_msg_handler(t_dtp *data, t_chat *chat) {
    t_gmsg *gmsg = mx_create_gmsg(data->json);

    if (!gmsg)
        return false;
    mx_add_message_to_room(gmsg, chat);
    return true;
}
