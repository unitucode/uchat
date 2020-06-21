#include "client.h"

static bool add_member(char *login, int user_id, int room_id, t_chat *chat) {
    t_groom *groom = mx_get_groom_by_id(room_id, chat->builder);

    if (g_hash_table_lookup(groom->members, GINT_TO_POINTER(user_id)))
        return false;
    g_hash_table_insert(groom->members, GINT_TO_POINTER(user_id), g_strdup(login));
    g_print("new user = %s\n", g_hash_table_lookup(groom->members, GINT_TO_POINTER(user_id)));
    return true;
}

bool mx_new_member_handler(t_dtp *data, t_chat *chat) {
    cJSON *login = cJSON_GetObjectItemCaseSensitive(data->json, "login");
    cJSON *id = cJSON_GetObjectItemCaseSensitive(data->json, "user_id");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");

    if (!cJSON_IsString(login))
        return false;
    if (!cJSON_IsNumber(id))
        return false;
    if (!cJSON_IsNumber(room_id))
        return false;
    if (!add_member(login->valuestring, id->valueint, room_id->valueint, chat))
        return false;
    return true;
}
