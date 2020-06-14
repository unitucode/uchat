#include "client.h"

t_dtp *mx_upload_file_request(char *name, int size) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_FILE))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "name", MX_J_STR(name)))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "size", size))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_upload_file_handler(t_dtp *data, t_chat *chat) {
    data++;
    chat++;
    return true;
}
