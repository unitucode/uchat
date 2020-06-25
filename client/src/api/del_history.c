#include "client.h"

t_dtp *mx_del_hist_request(int room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_DEL_HIST))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_del_hist_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");

    if (!cJSON_IsNumber(room_id))
        return false;
    g_message("DELETE HISTORY OF ROOM %d client/src/api/del_history.c\n", room_id->valueint);
    (void)room_id;
    (void)chat;
    return true;
}
