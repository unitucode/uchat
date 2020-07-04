#include "protocol.h"

/*
    Returned - The Malloced Data Transpart struct
*/
t_dtp *mx_get_transport_data(cJSON *json_result) {
    t_dtp *dtp = NULL;
    char *json_str = NULL;

    json_str = cJSON_PrintUnformatted(json_result);
    dtp = mx_request_creation(json_str);
    mx_free((void**)&json_str);
    cJSON_Delete(json_result);
    return dtp;
}
