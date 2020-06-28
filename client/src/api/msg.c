#include "client.h"

t_dtp *mx_msg_request(char *msg, int room_id) {
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

gboolean mx_msg_handler(t_dtp *data, t_chat *chat) {
    t_gmsg *gmsg = mx_create_gmsg(data->json, chat);
    t_groom *groom = NULL;

    if (!gmsg)
        return FALSE;
    mx_add_message_to_room_new(gmsg, chat);
    groom = mx_get_groom_by_id(gmsg->room_id, chat->builder);
    if (!groom)
        return FALSE;
    mx_widget_set_class(GTK_WIDGET(groom->label_name), "has-messages");
    groom->uploaded++;
    return TRUE;
}
