#include "client.h"

/*
 * Function: mx_get_room_request
 * -------------------------------
 * Creates get rooms request
 * 
 * date: date
 * 
 * returns: get rooms request
 */
t_dtp *mx_get_rooms_request(guint64 date) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_GET_ROOMS))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "date", date))
        return NULL;
    return mx_get_transport_data(json_result);
}

static void update_data(cJSON *data, guint64 room_id, t_chat *chat) {
    t_dtp *dtp = NULL;

    dtp = mx_get_transport_data(data);
    if (!mx_new_room_handler(dtp, chat)) {
        mx_free_request(&dtp);
        return;
    }
    mx_free_request(&dtp);
    dtp = mx_get_members_request(room_id);
    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    dtp = mx_get_new_msgs_request(0, room_id);
    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
} 

static void insert_room(cJSON *room, t_chat *chat) {
    cJSON *dup = cJSON_Duplicate(room, cJSON_True);
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(room, "id");

    if (!cJSON_IsNumber(room_id))
        return;
    if (!cJSON_AddNumberToObject(dup, "type", RQ_NEW_ROOM))
        return;
    update_data(dup, room_id->valuedouble, chat);
}

/*
 * Function: mx_rooms_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_rooms_hanlder(t_dtp *data, t_chat *chat) {
    cJSON *rooms = cJSON_GetObjectItemCaseSensitive(data->json, "rooms");
    cJSON *room = NULL;

    if (!cJSON_IsArray(rooms))
        return FALSE;
    for (gint i = 0; i < cJSON_GetArraySize(rooms); i++) {
        room = cJSON_GetArrayItem(rooms, i);
        insert_room(room, chat);
    }
    return TRUE;
}
