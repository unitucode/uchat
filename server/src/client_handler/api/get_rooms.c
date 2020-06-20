#include "server.h"

bool mx_get_rooms_handler(t_dtp *data, t_client *client) {
    cJSON *date = cJSON_GetObjectItemCaseSensitive(data->json, "date");
    t_dtp *rooms = NULL;
    cJSON *rooms_json = cJSON_CreateObject();

    if (!date || !cJSON_IsNumber(date))
        return false;
    if (!cJSON_AddItemReferenceToObject(rooms_json, "rooms",
                                        mx_get_rooms(client->info->database,
                                             date->valueint))) {
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
