#include "server.h"

t_dtp *mx_search_rooms_request(cJSON *array) {
    cJSON *res = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(res, "type", RQ_SEARCH_CH))
        return NULL;
    if (!cJSON_AddItemReferenceToObject(res, "rooms", array))
        return NULL;
    return mx_get_transport_data(res);
}

bool mx_search_rooms_handler(t_dtp *data, t_client *client) {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(data->json, "name");
    t_dtp *answer = NULL;

    if (!cJSON_IsString(name))
        return false;
    answer = mx_search_rooms_request(mx_search_room(client->info->database, name->valuestring));
    mx_send(client->out, answer);
    mx_free_request(&answer);
    return true;
}
