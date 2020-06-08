#include "client.h"

t_dtp *mx_get_rooms_request(long int date) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_GET_ROOMS))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "date", date))
        return NULL;
    return mx_get_transport_data(json_result);
}
