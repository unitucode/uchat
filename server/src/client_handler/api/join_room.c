#include "api.h"

static t_dtp *get_resend_room(t_db_room *room) {
    cJSON *send = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(send, "type", RQ_JOIN_ROOM))
        return NULL;
    if (!cJSON_AddStringToObject(send, "name", MX_J_STR(room->room_name)))
        return NULL;
    if (!cJSON_AddNumberToObject(send, "customer_id", room->customer_id))
        return NULL;
    if (!cJSON_AddNumberToObject(send, "id", room->room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(send, "date", room->date))
        return NULL;
    if (!cJSON_AddStringToObject(send, "desc", MX_J_STR(room->desc)))
        return NULL;
    if (!cJSON_AddNumberToObject((send), "power", room->power))
        return NULL;
    return mx_get_transport_data(send);
}

static t_dtp *new_member(char *login, guint64 user_id, guint64 room_id) {
    cJSON *member = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(member, "type", RQ_NEW_MEMBER))
        return NULL;
    if (!cJSON_AddNumberToObject(member, "user_id", user_id))
        return NULL;
    if (!cJSON_AddNumberToObject(member, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(member, "login", login))
        return NULL;
    return mx_get_transport_data(member);
}

static void resend(t_client *client, guint64 room_id) {
    t_dtp *answer = NULL;
    t_db_room *db_room = NULL;

    db_room = mx_get_room_by_id(client->info->database, room_id);
    answer = get_resend_room(db_room);
    mx_send(client->out, answer);
    mx_free_request(&answer);
    answer = new_member(client->user->login, client->user->user_id, room_id);
    mx_send_to_all(answer, client, room_id);
    mx_free_request(&answer);
    mx_free_room(&db_room);
}

/*
 * Function: mx_join_room_handler
 * -------------------------------
 * Handles request from client
 * 
 * room: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_join_room_handler(t_dtp *room, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(room->json, "room_id");

    if (!cJSON_IsNumber(room_id)
        || mx_is_member(client->info->database, client->user->user_id,
                        room_id->valueint)) {
        return FALSE;
    }
    mx_insert_member_into_db(client->info->database, room_id->valueint,
                             client->user->user_id, DB_SIMPLE);
    resend(client, room_id->valuedouble);
    return TRUE;
}
