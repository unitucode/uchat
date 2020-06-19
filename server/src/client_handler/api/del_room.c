#include "server.h"

static t_dtp *get_resend_room(int room_id) {
    cJSON *send = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(send, "type", RQ_DEL_ROOM))
        return NULL;
    if (!cJSON_AddNumberToObject(send, "room_id", room_id))
        return NULL;
    return mx_get_transport_data(send);
}



bool mx_del_room_handler(t_dtp *data, t_client *client) { //TODO leaks
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json,
                                                   "room_id");
    t_db_room *room = NULL;
    t_dtp *resend = NULL;

    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    room = mx_get_room_by_id(client->info->database, room_id->valueint);
    if (room && !strcmp(room->customer, client->user->login))
        mx_delete_room_by_id(client->info->database, room_id->valueint);
    else
        return false;
    resend = get_resend_room(room_id->valueint);
    mx_send_to_all(resend, client);
    mx_free_request(&resend);
    mx_free_room(&room);
    return true;
}
