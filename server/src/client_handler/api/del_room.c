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
    t_dtp *resend = NULL;

    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    if (mx_get_type_member(client->info->database, client->user->user_id, room_id->valueint) != DB_CUSTOMER)
        return false;
    mx_delete_room_by_id(client->info->database, room_id->valueint);
    resend = get_resend_room(room_id->valueint);
    mx_send_to_all(resend, client, room_id->valueint);
    mx_free_request(&resend);
    return true;
}
