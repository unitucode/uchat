#include "client.h"

/*
 * Function: mx_del_hist_request
 * -------------------------------
 * Creates delete history request
 * 
 * room_id: room id that need to clear
 * 
 * returns: delete history request
 */
t_dtp *mx_del_hist_request(guint64 room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_DEL_HIST))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_del_hist_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_del_hist_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");

    if (!cJSON_IsNumber(room_id))
        return FALSE;
    mx_gupd_clear_history(chat->builder, room_id->valuedouble);
    return TRUE;
}
