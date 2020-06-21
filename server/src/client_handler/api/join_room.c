#include "server.h"

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
    return mx_get_transport_data(send);
}

static t_dtp *new_member(char *login, int user_id, int room_id) {
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

bool mx_join_room_handler(t_dtp *room, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(room->json, "room_id");
    t_db_room *db_room = NULL;
    t_dtp *answer = NULL;

    if (!cJSON_IsNumber(room_id))
        return false;
    if (mx_is_member(client->info->database, client->user->user_id, room_id->valueint))
        return false;
    mx_insert_member_into_db(client->info->database, room_id->valueint, client->user->user_id, DB_SIMPLE);
    db_room = mx_get_room_by_id(client->info->database, room_id->valueint);
    answer = get_resend_room(db_room);
    mx_send(client->out, answer);
    mx_free_request(&answer);
    answer = new_member(client->user->login, client->user->user_id, room_id->valueint);
    mx_send_to_all(answer, client, room_id->valueint);
    mx_free_request(&answer);
    mx_free_room(&db_room);
    return true;
}
