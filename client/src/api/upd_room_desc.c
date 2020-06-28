#include "client.h"

/*
 * Function: mx_upd_room_desc_request
 * -------------------------------
 * Creates update room description request
 * 
 * room_id: room id
 * desc: new room description
 * 
 * returns: update room description
 */
t_dtp *mx_upd_room_desc_request(guint64 room_id, char *desc) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_ROOM_DESC))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", MX_J_STR(desc)))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_upd_room_desc_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_upd_room_desc_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(data->json, "desc");

    if (!cJSON_IsNumber(room_id))
        return FALSE;
    if (!cJSON_IsString(desc))
        return FALSE;
    mx_gupd_room_desc(room_id->valuedouble, desc->valuestring, chat->builder);
    return TRUE;
}
