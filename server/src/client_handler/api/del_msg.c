#include "server.h"

t_dtp *mx_del_msg_request(int room_id, int msg_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_DEL_MSG))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "msg_id", msg_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_del_msg_handler(t_dtp *msg, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(msg->json, "room_id");
    cJSON *msg_id = cJSON_GetObjectItemCaseSensitive(msg->json, "msg_id");
    t_dtp *resend = NULL;

    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    if (!msg_id || !cJSON_IsNumber(msg_id))
        return false;
    // mx_delete_message(client->info->database, room_id->valueint, msg_id->valueint);
    resend = mx_del_msg_request(room_id->valueint, msg_id->valueint);
    mx_send_to_all(resend, client);
    mx_free_request(&resend);
    return true;
}
