#include "client.h"

/*
 * Function: mx_search_rooms_request
 * -------------------------------
 * Creates search rooms request
 * 
 * room_name: start of room name
 * 
 * returns: search rooms request
 */
t_dtp *mx_search_rooms_request(char *room_name) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_SEARCH_CH))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "name", MX_J_STR(room_name)))
        return NULL;
    return mx_get_transport_data(json_result);
}

static gboolean handle_room(cJSON *room, t_chat *chat) {
    t_groom *groom = mx_create_groom(room);

    if (!groom)
        return FALSE;
    mx_add_room_row(groom, chat, MX_GLOBAL_ROOMS);
    return TRUE;
}

/*
 * Function: mx_searc_rooms_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_search_rooms_handler(t_dtp *data, t_chat *chat) {
    cJSON *rooms = cJSON_GetObjectItemCaseSensitive(data->json, "rooms");
    cJSON *room = NULL;

    if (!cJSON_IsArray(rooms))
        return FALSE;
    for (gint i = 0; i < cJSON_GetArraySize(rooms); i++) {
        room = cJSON_GetArrayItem(rooms, i);
        if (!handle_room(room, chat))
            return FALSE;
    }
    if (!cJSON_GetArraySize(rooms)) {
        mx_widget_set_visibility_by_name(chat->builder,
                                         "label_search_nothing_global", TRUE);
    }
    return TRUE;
}
