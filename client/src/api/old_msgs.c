#include "client.h"

t_dtp *mx_old_msgs_request(guint64 date, int room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_OLD_MSGS))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "date", date))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "count", MX_BUF_MSGS))
        return NULL;
    return mx_get_transport_data(json_result);
}

static void insert_msg(cJSON *room, t_chat *chat, int room_id) {
    cJSON *dup = cJSON_Duplicate(room, cJSON_True);
    t_gmsg *gmsg = NULL;

    if (!cJSON_AddNumberToObject(dup, "room_id", room_id))
        return;
    gmsg = mx_create_gmsg(dup, chat);
    mx_add_message_to_room_old(gmsg, chat);
}

bool mx_old_msgs_hanlder(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *msgs = cJSON_GetObjectItemCaseSensitive(data->json, "messages");
    cJSON *msg = NULL;

    if (!cJSON_IsNumber(room_id))
        return false;
    if (!cJSON_IsArray(msgs))
        return false;
    for (int i = 0; i < cJSON_GetArraySize(msgs); i++) {
        msg = cJSON_GetArrayItem(msgs, i);
        insert_msg(msg, chat, room_id->valueint);
    }
    chat->upl_old_msgs = false;
    (void)data;
    (void)chat;
    return true;
}
