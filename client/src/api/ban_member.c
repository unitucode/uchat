#include "client.h"

t_dtp *mx_ban_member_request(int room_id, int user_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_BAN_MEMBER))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "user_id", user_id))
        return NULL;
    return mx_get_transport_data(json_result);
}

static bool delete_member(t_chat *chat, int room_id, int user_id) {
    t_groom *groom = mx_get_groom_by_id(room_id, chat->builder);

    if (groom) {
        if (!g_hash_table_contains(groom->members, GINT_TO_POINTER(user_id)))
            return false;
        g_print("removed = %d\n", g_hash_table_remove(groom->members, GINT_TO_POINTER(user_id))); // TODO LEAKS
    }
    return true;
}

bool mx_ban_member_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *user_id = cJSON_GetObjectItemCaseSensitive(data->json, "user_id");

    if (!cJSON_IsNumber(room_id))
        return false;
    if (!cJSON_IsNumber(user_id))
        return false;
    if (!delete_member(chat, room_id->valueint, user_id->valueint))
        return false;
    mx_set_current_room_sett(chat->builder);
    return true;
}
