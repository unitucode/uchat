#include "client.h"

/*
 * Function: mx_search_msgs_request
 * -------------------------------
 * Creates search messages request
 * 
 * msg: start of message
 * 
 * returns: search messages request
 */
t_dtp *mx_search_msgs_request(char *msg, guint64 room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_SEARCH_MSG))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "msg", MX_J_STR(msg)))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

static gboolean handle_msg(cJSON *room, t_chat *chat) {
    t_gmsg *msg = mx_create_gmsg(room, chat);

    if (!msg)
        return FALSE;
    mx_add_message_to_found(msg, chat);
    return TRUE;
}

/*
 * Function: mx_search_msgs_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_search_msgs_handler(t_dtp *data, t_chat *chat) {
    cJSON *msgs = cJSON_GetObjectItemCaseSensitive(data->json, "msgs");
    cJSON *msg = NULL;

    if (!cJSON_IsArray(msgs))
        return FALSE;
    for (gint i = 0; i < cJSON_GetArraySize(msgs); i++) {
        msg = cJSON_GetArrayItem(msgs, i);
        if (!handle_msg(msg, chat))
            return FALSE;
    }
    if (!cJSON_GetArraySize(msgs)) {
        mx_widget_set_visibility_by_name(chat->builder,
                                         "label_search_nothing_msgs", TRUE);
    }
    return TRUE;
}
