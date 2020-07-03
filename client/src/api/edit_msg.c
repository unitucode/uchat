#include "client.h"

/*
 * Function: mx_edit_msg_request
 * -------------------------------
 * Creates edit message request
 * 
 * msg: edited message
 * room_id: room id that contains message
 * msg_id: message id that need to edit
 * 
 * returns: edit message request
 */
t_dtp *mx_edit_msg_request(char *msg, guint64 room_id, guint64 msg_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_EDIT_MSG))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "msg_id", msg_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "msg", MX_J_STR(msg)))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_edit_msg_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_edit_msg_handler(t_dtp *data, t_chat *chat) {
    cJSON *msg = cJSON_GetObjectItemCaseSensitive(data->json, "msg");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *msg_id = cJSON_GetObjectItemCaseSensitive(data->json, "msg_id");
    cJSON *power = cJSON_GetObjectItemCaseSensitive(data->json, "power");
    gdouble power_d = 0;

    if (!cJSON_IsString(msg) || !cJSON_IsNumber(room_id)
        || !cJSON_IsNumber(msg_id) || !cJSON_IsNumber(power)) {
        return FALSE;
    }
    power_d = mx_get_used_power(power->valuedouble);
    mx_gupd_msg_text(msg_id->valuedouble, room_id->valuedouble,
                     msg->valuestring, chat->builder);
    mx_gupd_msg_power(msg_id->valueint, room_id->valuedouble,
                      power_d, chat->builder);
    return TRUE;
}
