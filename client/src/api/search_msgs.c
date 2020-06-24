#include "client.h"

t_dtp *mx_search_msgs_request(char *msg, int room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_SEARCH_MSG))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "msg", MX_J_STR(msg)))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

static bool handle_msg(cJSON *room, t_chat *chat) {
    t_gmsg *msg = mx_create_gmsg(room, chat);

    if (!msg)
        return false;
    mx_add_message_to_found(msg, chat);
    (void)chat;
    (void)msg;
    return true;
}

bool mx_search_msgs_handler(t_dtp *data, t_chat *chat) {
    cJSON *msgs = cJSON_GetObjectItemCaseSensitive(data->json, "msgs");
    cJSON *msg = NULL;

    if (!cJSON_IsArray(msgs))
        return false;
    for (int i = 0; i < cJSON_GetArraySize(msgs); i++) {
        msg = cJSON_GetArrayItem(msgs, i);
        if (!handle_msg(msg, chat))
            return false;
    }
    if (!cJSON_GetArraySize(msgs)) {
        mx_widget_set_visibility_by_name(chat->builder,
                                        "label_search_nothing_msgs", TRUE);
    }
    return true;
}
