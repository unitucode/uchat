#include "client.h"

bool mx_update_users_handler(t_dtp *data, t_chat *chat) {
    cJSON *online = cJSON_GetObjectItemCaseSensitive(data->json, "online");
    cJSON *all_users = cJSON_GetObjectItemCaseSensitive(data->json, "all");

    if (!online || !cJSON_IsNumber(online))
        return false;
    if (!all_users || !cJSON_IsNumber(all_users))
        return false;
    chat++; // TODO
    printf("online users = %d all users = %d\n", online->valueint, all_users->valueint);
    return true;
}
