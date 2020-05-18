#include "protocol.h"

t_dtp *mx_new_room_request(char *room_name, bool is_private) {
    t_dtp *dtp = NULL;
    cJSON *json_result = cJSON_CreateObject();
    char *json_str = NULL;

    if (!cJSON_AddNumberToObject(json_result, "type", MX_NEW_ROOM))
        return NULL;
    if (!cJSON_AddBoolToObject(json_result, "is_private", is_private))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "room_name", MX_J_STR(room_name)))
        return NULL;
    json_str = cJSON_Print(json_result);
    dtp = mx_request_creation(json_str);
    mx_free((void**)&json_str);
    cJSON_Delete(json_result);
    return dtp;
}

t_dtp *mx_delete_room_request(char *room_name) {
    t_dtp *dtp = NULL;
    cJSON *json_result = cJSON_CreateObject();
    char *json_str = NULL;

    if (!cJSON_AddNumberToObject(json_result, "type", MX_DELETE_ROOM))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "room_name", MX_J_STR(room_name)))
        return NULL;
    json_str = cJSON_Print(json_result);
    dtp = mx_request_creation(json_str);
    mx_free((void**)&json_str);
    cJSON_Delete(json_result);
    return dtp;
}
