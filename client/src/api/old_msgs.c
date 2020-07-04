#include "client.h"

/*
 * Function: mx_old_msgs_request
 * -------------------------------
 * Creates old messages request
 * 
 * date: date
 * room_id: room that contains messages
 * 
 * returns: old messages request
 */
t_dtp *mx_old_msgs_request(guint64 date, guint64 room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_OLD_MSGS))
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
    cJSON *dup = cJSON_Duplicate(room, cJSON_True);
    t_gmsg *gmsg = NULL;

    if (!cJSON_AddNumberToObject(dup, "room_id", room_id))
        return;
    gmsg = mx_create_gmsg(dup, chat);
    if (!gmsg) {
        cJSON_Delete(dup);
        return;
    }
    mx_add_message_to_room_old(gmsg, chat);
    cJSON_Delete(dup);
}

/*
 * Function: mx_old_msgs_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_old_msgs_hanlder(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *msgs = cJSON_GetObjectItemCaseSensitive(data->json, "messages");
    t_groom *groom = NULL;
    cJSON *msg = NULL;

    if (!cJSON_IsNumber(room_id) || !cJSON_IsArray(msgs))
        return FALSE;
    for (gint i = 0; i < cJSON_GetArraySize(msgs); i++) {
        msg = cJSON_GetArrayItem(msgs, i);
        insert_msg(msg, chat, room_id->valuedouble);
    }
    groom = mx_get_groom_by_id(room_id->valuedouble, chat->builder);
    if (!groom)
        return FALSE;
    groom->uploaded += cJSON_GetArraySize(msgs);
    chat->upl_old_msgs = FALSE;
    return TRUE;
}
