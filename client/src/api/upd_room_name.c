#include "client.h"

t_dtp *mx_upd_room_name_request(int room_id, char *name) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_ROOM_NAME))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "room_name", MX_J_STR(name)))
        return NULL;
    return mx_get_transport_data(json_result);
}
