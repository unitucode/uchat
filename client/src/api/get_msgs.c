#include "client.h"

/*
 * Function: mx_get_new_msgs_request
 * -------------------------------
 * Creates get new messages request
 * 
 * date: date
 * room_id: room id
 * 
 * returns: get new message request
 */
t_dtp *mx_get_new_msgs_request(guint64 date, guint64 room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_GET_NEW_MSGS))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "date", date))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "count", MX_BUF_MSGS))
        return NULL;
    return mx_get_transport_data(json_result);
}

static void insert_msg(cJSON *room, t_chat *chat, guint64 room_id) {
    t_dtp *dtp = NULL;
    cJSON *dup = cJSON_Duplicate(room, cJSON_True);

    if (!cJSON_AddNumberToObject(dup, "type", RQ_MSG))
        return;
    if (!cJSON_AddNumberToObject(dup, "room_id", room_id))
        return;
    dtp = mx_get_transport_data(dup);
    mx_msg_handler(dtp, chat);
    mx_free_request(&dtp);
}

/*
 * Function: mx_new_msgs_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_new_msgs_hanlder(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *msgs = cJSON_GetObjectItemCaseSensitive(data->json, "messages");
    cJSON *msg = NULL;

    if (!cJSON_IsNumber(room_id) || !cJSON_IsArray(msgs))
        return FALSE;
    for (gint i = cJSON_GetArraySize(msgs) - 1; i >= 0; i--) {
        msg = cJSON_GetArrayItem(msgs, i);
        insert_msg(msg, chat, room_id->valuedouble);
    }
    return TRUE;
}
