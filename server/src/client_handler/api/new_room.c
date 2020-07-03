#include "api.h"

/*
 * Function: get_resend_room
 * -------------------------------
 * Creates request "new room"
 * 
 * room: information about room in database
 * 
 * returns: new request
 */
static t_dtp *get_resend_room(t_db_room *room) {
    cJSON *send = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(send, "type", RQ_NEW_ROOM))
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
    if (!cJSON_AddNumberToObject(send, "power", room->power))
        return NULL;
    return mx_get_transport_data(send);
}

static gboolean is_valid(t_db_room *room) {
    gsize len = 0;

    if (!room)
        return FALSE;
    len = strlen(room->room_name);
    if (len <= 0 || len > MX_MAX_ROOM_NAME)
        return FALSE;
    return TRUE;
}

/*
 * Function: mx_new_room_handler
 * -------------------------------
 * Handles request from client
 * 
 * data: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_new_room_handler(t_dtp *data, t_client *client) {
    t_db_room *room = mx_parse_json_room(data->json);
    t_dtp *resend = NULL;

    if (!is_valid(room))
        return FALSE;
    room->customer_id = client->user->user_id;
    mx_insert_room_into_db(client->info->database, room);
    resend = get_resend_room(room);
    mx_free_room(&room);
    if (!resend)
        return FALSE;
    mx_send(client->out, resend);
    mx_free_request(&resend);
    return TRUE;
}
