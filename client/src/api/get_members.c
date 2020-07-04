#include "client.h"

/*
 * Function: mx_get_members_request
 * -------------------------------
 * Creates get members request
 * 
 * room_id: room id that contains members
 * 
 * returns: get members request
 */
t_dtp *mx_get_members_request(guint64 room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_GET_MEMBERS))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

static gboolean insert_member(cJSON *member, guint64 room_id, t_chat *chat) {
    cJSON *login = cJSON_GetObjectItemCaseSensitive(member, "login");
    cJSON *id = cJSON_GetObjectItemCaseSensitive(member, "id");
    t_groom *groom = NULL;

    if (!cJSON_IsString(login) || !cJSON_IsNumber(id))
        return FALSE;
    groom = mx_get_groom_by_id(room_id, chat->builder);
    if (!groom)
        return FALSE;
    if (groom->customer_id == (guint64)id->valuedouble)
        groom->customer = g_strdup(login->valuestring);
    g_hash_table_insert(groom->members,
                        GINT_TO_POINTER((guint64)id->valuedouble),
                        g_strdup(login->valuestring));
    return TRUE;
}

/*
 * Function: mx_get_members_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_get_members_handler(t_dtp *data, t_chat *chat) {
    cJSON *members = cJSON_GetObjectItemCaseSensitive(data->json, "members");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *member = NULL;

    if (!cJSON_IsArray(members) || !cJSON_IsNumber(room_id))
        return FALSE;
    for (gint i = 0; i < cJSON_GetArraySize(members); i++) {
        member = cJSON_GetArrayItem(members, i);
        if (!insert_member(member, room_id->valuedouble, chat))
            return FALSE;
    }
    return TRUE;
}
