#include "client.h"

/*
 * Function: mx_new_room_request
 * -------------------------------
 * Creates new room request
 * 
 * room_name: room name
 * desc: description of room
 * type: type of room
 * 
 * returns: new room request
 */
t_dtp *mx_new_room_request(char *room_name, char *desc, t_room_type type) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_NEW_ROOM))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "name", MX_J_STR(room_name)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", MX_J_STR(desc)))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "type", type))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_new_room_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_new_room_handler(t_dtp *data, t_chat *chat) {
    t_groom *room = NULL;
    t_dtp *members = NULL;

    room = mx_create_groom(data->json);
    if (!room)
        return FALSE;
    members = mx_get_members_request(room->id);
    mx_send(chat->out, members);
    mx_free_request(&members);
    mx_add_groom(room, chat);
    return TRUE;
}
