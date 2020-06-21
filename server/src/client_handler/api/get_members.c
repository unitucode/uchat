#include "server.h"

bool mx_get_members_handler(t_dtp *data, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *members = cJSON_CreateObject();
    t_dtp *answer = NULL;

    if (!cJSON_IsNumber(room_id))
        return false;
    if (!mx_is_member(client->info->database, client->user->user_id, room_id->valueint))
        return false;
    if (!cJSON_AddItemReferenceToObject(members, "members", mx_get_json_members(client->info->database, room_id->valueint))) {
        cJSON_Delete(members);
        return false;
    }
    if (!cJSON_AddNumberToObject(members, "room_id", room_id->valueint)) {
        cJSON_Delete(members);
        return false;
    }
    if (!cJSON_AddNumberToObject(members, "type", RQ_GET_MEMBERS)) {
        cJSON_Delete(members);
        return false;
    }
    answer = mx_get_transport_data(members);
    mx_send(client->out, answer);
    mx_free_request(&answer);
    return true;
}
