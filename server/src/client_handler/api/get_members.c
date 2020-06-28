#include "api.h"

static gboolean is_valid(t_client *client, guint64 room_id) {
    if (mx_get_type_member(client->info->database, client->user->user_id,
                           room_id) == DB_BANNED) {
        return FALSE;
    }
    if (!mx_is_member(client->info->database, client->user->user_id,
                      room_id)) {
        return FALSE;
    }
    return TRUE;
}

static gboolean resend(t_client *client, guint64 room_id) {
    cJSON *members = cJSON_CreateObject();
    cJSON *json_members = mx_get_json_members(client->info->database,
                                              room_id);
    t_dtp *answer = NULL;

    if (!cJSON_AddItemReferenceToObject(members, "members", json_members)
        || !cJSON_AddNumberToObject(members, "room_id", room_id)
        || !cJSON_AddNumberToObject(members, "type", RQ_GET_MEMBERS)) {
        cJSON_Delete(members);
        return FALSE;
    }
    answer = mx_get_transport_data(members);
    mx_send(client->out, answer);
    mx_free_request(&answer);
    return TRUE;
}

/*
 * Function: mx_get_members_handler
 * -------------------------------
 * Handles request from client and send all members to client
 * 
 * data: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_get_members_handler(t_dtp *data, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");

    if (!cJSON_IsNumber(room_id))
        return FALSE;
    if (!is_valid(client, room_id->valuedouble))
        return FALSE;
    if (!resend(client, room_id->valuedouble))
        return FALSE;
    return TRUE;
}
