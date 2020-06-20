#include "server.h"

bool mx_get_msgs_handler(t_dtp *data, t_client *client) {
    cJSON *date = cJSON_GetObjectItemCaseSensitive(data->json, "date");
    cJSON *count = cJSON_GetObjectItemCaseSensitive(data->json, "count");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    t_dtp *msgs = NULL;
    cJSON *msgs_json = NULL;

    if (!date || !cJSON_IsNumber(date))
        return false;
    if (!count || !cJSON_IsNumber(count))
        return false;
    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    msgs_json = mx_get_new_messages_by_id(client->info->database, room_id->valueint, date->valueint, count->valueint);
    if (!cJSON_AddNumberToObject(msgs_json, "type", RQ_GET_NEW_MSGS)) {
        cJSON_Delete(msgs_json);
        return false;
    }
    msgs = mx_get_transport_data(msgs_json);
    mx_send(client->out, msgs);
    mx_free_request(&msgs);
    return true;
}
