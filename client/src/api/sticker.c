#include "client.h"

t_dtp *mx_sticker_request(int id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_STICKER))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "id", id))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_sticker_handler(t_dtp *data, t_chat *chat) {
    
    return true;
}
