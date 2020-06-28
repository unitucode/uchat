#include "client.h"

/*
 * Function: mx_del_msg_request
 * -------------------------------
 * Creates delete message request
 * 
 * room_id: room id that contains message
 * msg_id: message id that need to delete
 * 
 * returns: delete message request
 */
t_dtp *mx_del_msg_request(guint64 room_id, guint64 msg_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_DEL_MSG))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "msg_id", msg_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_del_msg_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_del_msg_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *msg_id = cJSON_GetObjectItemCaseSensitive(data->json, "msg_id");

    if (!cJSON_IsNumber(room_id) || !cJSON_IsNumber(msg_id))
        return FALSE;
    mx_gdel_msg(msg_id->valuedouble, room_id->valuedouble, chat->builder);
    return TRUE;
}
