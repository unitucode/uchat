#include "client.h"

t_dtp *mx_new_room_request(char *room_name, bool is_private, char *pass) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_NEW_ROOM))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "room_name", MX_J_STR(room_name)))
        return NULL;
    if (!cJSON_AddBoolToObject(json_result, "is_private", is_private))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "pass", MX_J_STR(pass)))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_new_room(t_dtp *data, t_chat *chat) {
    cJSON *room_name = cJSON_GetObjectItemCaseSensitive(data->json,
                                                        "room_name");
    cJSON *customer = cJSON_GetObjectItemCaseSensitive(data->json,
                                                       "customer");
    cJSON *id = cJSON_GetObjectItemCaseSensitive(data->json, "id");
    cJSON *date = cJSON_GetObjectItemCaseSensitive(data->json, "date");
    t_groom *room = NULL;

    if (!room_name || !cJSON_IsString(room_name))
        return false;
    if (!customer || !cJSON_IsString(customer))
        return false;
    if (!id || !cJSON_IsNumber(id))
        return false;
    if (!date || !cJSON_IsNumber(date))
        return false;
    room = mx_create_groom(room_name->valuestring, customer->valuestring,
                           id->valueint, date->valueint);
    mx_add_groom(room, chat->builder);
    return true;
}
