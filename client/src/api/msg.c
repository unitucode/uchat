#include "client.h"

/*
 * Function: mx_msg_request
 * -------------------------------
 * Creates message with TEXT type request
 * 
 * msg: message
 * room_id: room id for message
 * 
 * returns: message request
 */
t_dtp *mx_msg_request(char *msg, guint64 room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_MSG))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "message", MX_J_STR(msg)))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "msg_type", DB_TEXT_MSG))
        return NULL;
    return mx_get_transport_data(json_result);
}

/*
 * Function: mx_msg_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_msg_handler(t_dtp *data, t_chat *chat) {
    t_gmsg *gmsg = mx_create_gmsg(data->json, chat);
    t_groom *groom = NULL;

    if (!gmsg)
        return FALSE;
    mx_add_message_to_room_new(gmsg, chat);
    groom = mx_get_groom_by_id(gmsg->room_id, chat->builder);
    if (!groom)
        return FALSE;
    if (g_strcmp0(gmsg->login, chat->login))
        mx_widget_set_class(GTK_WIDGET(groom->label_name), "has-messages");
    groom->uploaded++;
    return TRUE;
}
