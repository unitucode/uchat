#include "client.h"

static void gupd_room_desc(int id, char *desc, GtkBuilder *builder) {
    t_groom *groom = mx_get_groom_by_id(id, builder);

    mx_free((void **)&(groom->desc));
    groom->desc = strdup(desc);
    mx_set_current_room_sett(builder);
}

t_dtp *mx_upd_room_desc_request(int room_id, char *desc) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_ROOM_DESC))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", MX_J_STR(desc)))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_upd_room_desc_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(data->json, "desc");

    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    if (!desc || !cJSON_IsString(desc))
        return false;
    gupd_room_desc(room_id->valueint, desc->valuestring, chat->builder);
    return true;
}
