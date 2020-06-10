#include "client.h"

bool mx_update_users(t_dtp *data, t_chat *chat) {
    cJSON *users = cJSON_GetObjectItemCaseSensitive(data->json, "online");
    chat++; // TODO

    if (!users || !cJSON_IsNumber(users))
        return false;
    printf("online users = %d\n", users->valueint);
    return true;
}
