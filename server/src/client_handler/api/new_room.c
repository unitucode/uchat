#include "server.h"

static t_dtp *get_resend_room(t_db_room *room) {
    cJSON *send = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(send, "type", RQ_NEW_ROOM))
        return NULL;
    if (!cJSON_AddStringToObject(send, "name", MX_J_STR(room->room_name)))
        return NULL;
    if (!cJSON_AddStringToObject(send, "customer_id", MX_J_STR(room->customer_id)))
        return NULL;
    if (!cJSON_AddNumberToObject(send, "id", room->room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(send, "date", room->date))
        return NULL;
    if (!cJSON_AddStringToObject(send, "desc", room->desc))
        return NULL;
    return mx_get_transport_data(send);
}

bool mx_new_room_handler(t_dtp *data, t_client *client) { //TODO leaks
    t_db_room *room = mx_parse_json_room(data->json);
    t_dtp *resend = NULL;
    room->customer_id = client->user->user_id;

    if (!room)
        return false;
    mx_insert_room_into_db(client->info->database, room);
    resend = get_resend_room(room);
    mx_free_room(&room);
    if (!resend)
        return false;
    mx_send_to_all(resend, client);
    mx_free_request(&resend);
    return true;
}
