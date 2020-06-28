#include "client.h"

/*
 * Function: mx_del_room_request
 * -------------------------------
 * Creates delete room request
 * 
 * room_id: room id that need delete
 * 
 * returns: delete room request
 */
t_dtp *mx_del_room_request(guint64 room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_DEL_ROOM))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_del_room_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_del_room_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");

    if (!cJSON_IsNumber(room_id))
        return FALSE;
    mx_gdel_room(room_id->valuedouble, chat->builder);
    return TRUE;
}
