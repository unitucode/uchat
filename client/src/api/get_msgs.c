#include "client.h"

t_dtp *mx_get_new_msgs_request(long int date) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_GET_NEW_MSGS))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "date", date))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "count", MX_BUF_MSGS))
        return NULL;
    return mx_get_transport_data(json_result);
}

static void insert_msg(cJSON *room, t_chat *chat) {
    t_dtp *dtp = NULL;
    cJSON *dup = cJSON_Duplicate(room, cJSON_True);

    if (!cJSON_AddNumberToObject(dup, "type", RQ_MSG))
        return;
    dtp = mx_get_transport_data(dup);
    mx_msg(dtp, chat);
    mx_free_request(&dtp);
}

bool mx_new_msgs_hanlder(t_dtp *data, t_chat *chat) {
    cJSON *msgs = cJSON_GetObjectItemCaseSensitive(data->json, "rooms");
    cJSON *msg = NULL;

    if (!msgs || !cJSON_IsArray(msgs))
        return false;
    for (int i = 0; i < cJSON_GetArraySize(msgs); i++) {
        msg = cJSON_GetArrayItem(msgs, i);
        insert_msg(msg, chat);
    }
    return true;
}
