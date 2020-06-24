#include "client.h"

t_dtp *mx_search_rooms_request(char *room_name) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_SEARCH_CH))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "name", MX_J_STR(room_name)))
        return NULL;
    return mx_get_transport_data(json_result);
}

static bool handle_room(cJSON *room, t_chat *chat) {
    t_groom *groom = mx_create_groom(room);

    if (!groom)
        return false;
    mx_add_room_row(groom, chat->builder, MX_GLOBAL_ROOMS);
    return true;
}

bool mx_search_rooms_handler(t_dtp *data, t_chat *chat) {
    g_print("data = %s\n", cJSON_Print(data->json));
    cJSON *rooms = cJSON_GetObjectItemCaseSensitive(data->json, "rooms");
    cJSON *room = NULL;

    if (!cJSON_IsArray(rooms))
        return false;
    for (int i = 0; i < cJSON_GetArraySize(rooms); i++) {
        room = cJSON_GetArrayItem(rooms, i);
        if (!handle_room(room, chat))
            return false;
    }
    if (!cJSON_GetArraySize(rooms)) {
        mx_widget_set_visibility_by_name(chat->builder,
                                         "label_search_nothing_global", TRUE);
    }
    return true;
}
