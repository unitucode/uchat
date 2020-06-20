#include "client.h"

t_dtp *mx_search_rooms_request(char *room_name) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_SEARCH_CH))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "name", MX_J_STR(room_name)))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_search_rooms_handler(t_dtp *data, t_chat *chat) {
    g_print("data = %s\n", cJSON_Print(data->json));
    (void)chat;
    return true;
}
