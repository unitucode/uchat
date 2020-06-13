#include "client.h"

t_dtp *mx_new_room_request(char *room_name, char *desc) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_NEW_ROOM))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "room_name", MX_J_STR(room_name)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", MX_J_STR(desc)))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_new_room_handler(t_dtp *data, t_chat *chat) {
    t_groom *room = NULL;

    room = mx_create_groom(data->json);
    if (!room)
        return false;
    mx_add_groom(room, chat->builder);
    return true;
}
