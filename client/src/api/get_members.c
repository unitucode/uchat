#include "client.h"

t_dtp *mx_get_members_request(int room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_GET_MEMBERS))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

static bool insert_member(cJSON *member, int room_id, t_chat *chat) {
    cJSON *login = cJSON_GetObjectItemCaseSensitive(member, "login");
    cJSON *id = cJSON_GetObjectItemCaseSensitive(member, "id");
    t_groom *groom = NULL;

    if (!cJSON_IsString(login))
        return false;
    if (!cJSON_IsNumber(id))
        return false;
    groom = mx_get_groom_by_id(room_id, chat->builder);
    g_hash_table_insert(groom->members, GINT_TO_POINTER(id->valueint), g_strdup(login->valuestring));
    return true;
}

bool mx_get_members_handler(t_dtp *data, t_chat *chat) {
    cJSON *members = cJSON_GetObjectItemCaseSensitive(data->json, "members");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *member = NULL;

    if (!cJSON_IsArray(members))
        return false;
    if (!cJSON_IsNumber(room_id))
        return false;
    for (int i = 0; i < cJSON_GetArraySize(members); i++) {
        member = cJSON_GetArrayItem(members, i);
        if (!insert_member(member, room_id->valueint, chat))
            return false;
    }
    return true;
}
