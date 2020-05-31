#include "protocol.h"

t_dtp *mx_get_transport_data(cJSON *json_result) { // returns request structure
    t_dtp *dtp = NULL;
    char *json_str = NULL;

    json_str = cJSON_Print(json_result);
    dtp = mx_request_creation(json_str);
    mx_free((void**)&json_str);
    cJSON_Delete(json_result);
    return dtp;
}
