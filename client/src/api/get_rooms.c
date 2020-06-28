#include "client.h"

t_dtp *mx_get_rooms_request(long int date) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_GET_ROOMS))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "date", date))
        return NULL;
    return mx_get_transport_data(json_result);
}

static void insert_room(cJSON *room, t_chat *chat) { //TODO HANDLE ROOMS
    t_dtp *dtp = NULL;
    t_dtp *msgs = NULL;
    t_dtp *members = NULL;
    cJSON *dup = cJSON_Duplicate(room, cJSON_True);
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(room, "id");

    if (!cJSON_IsNumber(room_id))
        return;
    if (!cJSON_AddNumberToObject(dup, "type", RQ_NEW_ROOM))
        return;
    dtp = mx_get_transport_data(dup);
    mx_new_room_handler(dtp, chat);
    members = mx_get_members_request(room_id->valueint);
    mx_send(chat->out, members);
    msgs = mx_get_new_msgs_request(0, room_id->valueint);
    mx_send(chat->out, msgs);
    mx_free_request(&dtp);
    mx_free_request(&msgs);
    mx_free_request(&members);
}

gboolean mx_rooms_hanlder(t_dtp *data, t_chat *chat) {
    cJSON *rooms = cJSON_GetObjectItemCaseSensitive(data->json, "rooms");
    cJSON *room = NULL;

    if (!cJSON_IsArray(rooms))
        return FALSE;
    for (int i = 0; i < cJSON_GetArraySize(rooms); i++) {
        room = cJSON_GetArrayItem(rooms, i);
        insert_room(room, chat);
    }
    return TRUE;
}
