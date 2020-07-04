#include "api.h"

/*
 * Function: mx_ban_member_request
 * -------------------------------
 * Creates request "member ban"
 * 
 * room_id: id of rooms with this member
 * user_id: id of user that need to ban
 * 
 * returns: new request
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

static void ban_member(t_client *client, guint64 user_id, guint64 room_id) {
    t_db_user *member = mx_get_user_by_id(client->info->database, user_id);
    GDataOutputStream *out = g_hash_table_lookup(client->info->users,
                                                 member->login);
    t_dtp *del_room = mx_delete_room_request(room_id);

    if (out)
        mx_send(out, del_room);
    mx_free_user(&member);
    mx_free_request(&del_room);
}

static gboolean is_valid(t_client *client, guint64 room_id, guint64 user_id) {
    if (mx_get_type_member(client->info->database, client->user->user_id,
                           room_id) != DB_CUSTOMER) {
        return FALSE;
    }
    if (!mx_is_member(client->info->database, user_id, room_id))
        return FALSE;
    return TRUE;
}

/*
 * Function: mx_ban_member_handler
 * -------------------------------
 * Handles request from client
 * 
 * ban: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_ban_member_handler(t_dtp *ban, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(ban->json, "room_id");
    cJSON *user_id = cJSON_GetObjectItemCaseSensitive(ban->json, "user_id");
    t_dtp *answer = NULL;

    if (!cJSON_IsNumber(room_id) || !cJSON_IsNumber(user_id)
        || !is_valid(client, room_id->valuedouble, user_id->valuedouble)) {
       return FALSE;
    }
    mx_edit_type_member(client->info->database, room_id->valueint,
                        user_id->valueint, DB_BANNED);
    ban_member(client, user_id->valueint, room_id->valueint);
    answer = mx_ban_member_request(room_id->valueint, user_id->valueint);
    mx_send_to_all(answer, client, room_id->valueint);
    mx_free_request(&answer);
    return TRUE;
}
