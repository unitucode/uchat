#include "client.h"

static gboolean add_member(char *login, guint64 user_id, guint64 room_id,
                           t_chat *chat) {
    t_groom *groom = mx_get_groom_by_id(room_id, chat->builder);

    if (!groom)
        return FALSE;
    if (g_hash_table_lookup(groom->members, GINT_TO_POINTER(user_id)))
        return FALSE;
    g_hash_table_insert(groom->members, GINT_TO_POINTER(user_id),
                        g_strdup(login));
    return TRUE;
}

/*
 * Function: mx_new_member_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_new_member_handler(t_dtp *data, t_chat *chat) {
    cJSON *login = cJSON_GetObjectItemCaseSensitive(data->json, "login");
    cJSON *id = cJSON_GetObjectItemCaseSensitive(data->json, "user_id");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");

    if (!cJSON_IsString(login) || !cJSON_IsNumber(id)
        || !cJSON_IsNumber(room_id)) {
        return FALSE;
    }
    if (!add_member(login->valuestring, id->valuedouble,
                    room_id->valuedouble, chat)) {
        return FALSE;
    }
    return TRUE;
}
