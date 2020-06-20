#include "server.h"

bool mx_get_rooms_handler(t_dtp *data, t_client *client) {
    // // t_dtp *rooms = NULL;
    // cJSON *rooms_json = cJSON_CreateObject();

    // rooms = mx_get_transport_data(rooms_json);
    // mx_send(client->ssl, rooms);
    // mx_free_request(&rooms);
    cJSON *date = cJSON_GetObjectItemCaseSensitive(data->json, "date");
    cJSON *rooms_json = cJSON_CreateObject();
    t_dtp *rooms = NULL;

    if (!date || !cJSON_IsNumber(date))
        return false;
    if (!cJSON_AddItemReferenceToObject(rooms_json, "rooms", mx_get_rooms(client->info->database, date->valueint, client->user->user_id))) {
        cJSON_Delete(rooms_json);
        return false;
    }
    if (!cJSON_AddNumberToObject(rooms_json, "type", RQ_GET_ROOMS)) {
        cJSON_Delete(rooms_json);
        return false;
    }
    rooms = mx_get_transport_data(rooms_json);
    mx_send(client->out, rooms);
    mx_free_request(&rooms);
    return true;
}


