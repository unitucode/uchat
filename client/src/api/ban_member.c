#include "client.h"

/*
 * Function: mx_ban_member_request
 * -------------------------------
 * Creates ban member request
 * 
 * room_id: room id that contains user
 * user_id: user id that need to ban
 * 
 * returns: ban member request
 */
t_dtp *mx_ban_member_request(guint64 room_id, guint64 user_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_BAN_MEMBER))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "user_id", user_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

static gboolean delete_member(t_chat *chat, guint64 room_id,
                              guint64 user_id) {
    t_groom *groom = mx_get_groom_by_id(room_id, chat->builder);

    if (groom) {
        if (!g_hash_table_contains(groom->members, GINT_TO_POINTER(user_id)))
            return FALSE;
        g_hash_table_remove(groom->members, GINT_TO_POINTER(user_id));
        return TRUE;
    }
    return FALSE;
}

/*
 * Function: mx_ban_member_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_ban_member_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *user_id = cJSON_GetObjectItemCaseSensitive(data->json, "user_id");

    if (!cJSON_IsNumber(room_id) || !cJSON_IsNumber(user_id))
        return FALSE;
    if (!delete_member(chat, room_id->valuedouble, user_id->valuedouble))
        return FALSE;
    return TRUE;
}
