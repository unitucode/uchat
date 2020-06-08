#include "server.h"

bool mx_get_msgs_handler(t_dtp *data, t_client *client) {
    cJSON *date = cJSON_GetObjectItemCaseSensitive(data->json, "date");
    cJSON *count = cJSON_GetObjectItemCaseSensitive(data->json, "count");
    t_dtp *rooms = NULL;
    cJSON *rooms_json = cJSON_CreateObject();

    if (!date || !cJSON_IsNumber(date))
        return false;
    if (!count || !cJSON_IsNumber(count))
        return false;
    if (!cJSON_AddItemReferenceToObject(rooms_json, "msgs", ) {
        cJSON_Delete(rooms_json);
        return false;
    }
    if (!cJSON_AddNumberToObject(rooms_json, "type", RQ_GET_ROOMS)) {
        cJSON_Delete(rooms_json);
        return false;
    }
    rooms = mx_get_transport_data(rooms_json);
    mx_send(client->ssl, rooms);
    mx_free_request(&rooms);
    return true;
}
