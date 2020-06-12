#include "client.h"

void mx_gupd_room_name(int id, char *name, GtkBuilder *builder) {
    t_groom *groom = mx_get_groom_by_id(id, builder);
    groom->room_name = name;
    // SET NEW NAME ON LABEL
}

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

bool mx_upd_room_name_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *room_name = cJSON_GetObjectItemCaseSensitive(data->json, "room_name");

    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    if (!room_name || !cJSON_IsString(room_name))
        return false;
    mx_gupd_room_name(room_id->valueint, room_name->valuestring,
                      chat->builder);
    return true;
}
