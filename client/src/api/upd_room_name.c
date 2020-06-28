#include "client.h"

/*
 * Function: mx_upd_room_name_request
 * -------------------------------
 * Creates update room name request
 * 
 * room_id: room id
 * name: new room name
 * 
 * returns: update room name request
 */
t_dtp *mx_upd_room_name_request(guint64 room_id, char *name) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_ROOM_NAME))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "room_name", MX_J_STR(name)))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_upd_room_name_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_upd_room_name_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *room_name = cJSON_GetObjectItemCaseSensitive(data->json,
                                                        "room_name");

    if (!cJSON_IsNumber(room_id) || !cJSON_IsString(room_name))
        return FALSE;
    mx_gupd_room_name(room_id->valuedouble, room_name->valuestring,
                      chat->builder);
    return TRUE;
}
