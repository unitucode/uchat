#include "server.h"

static t_dtp *get_resend_room(t_db_room *room) {
    cJSON *send = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(send, "type", RQ_NEW_ROOM))
        return NULL;
    if (!cJSON_AddStringToObject(send, "room_name", MX_J_STR(room->name_room)))
        return NULL;
    if (!cJSON_AddStringToObject(send, "customer", MX_J_STR(room->customer)))
        return NULL;
    if (!cJSON_AddNumberToObject(send, "id", room->id))
        return NULL;
    if (!cJSON_AddNumberToObject(send, "date", room->date))
        return NULL;
    return mx_get_transport_data(send);
}

bool mx_new_room_handler(t_dtp *data, t_client *client) { //TODO leaks
    cJSON *room = cJSON_GetObjectItemCaseSensitive(data->json,
                                                   "room_name");
    t_db_room *new_room = NULL;
    t_dtp *resend = NULL;

    if (!room || !cJSON_IsString(room))
        return false;
    new_room = mx_insert_room_into_db(client->chat->database,
                                      room->valuestring,
                                      (char*)client->user->login);
    if (!new_room)
        return false;
    resend = get_resend_room(new_room);
    if (!resend)
        return false;
    mx_send_to_all(resend, client);
    mx_free_request(&resend);
    return true;
}
