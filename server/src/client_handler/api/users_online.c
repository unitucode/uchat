#include "server.h"

t_dtp *mx_users_online_request(int count, int all) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_USERS_ONLINE))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "online", count))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "all", all))
        return NULL;
    return mx_get_transport_data(json_result);
}

void mx_update_online(int count, t_client *client) {
    t_dtp *users = NULL;
    int all_users = mx_get_count_users(client->info->database);

    users = mx_users_online_request(count, all_users);
    // mx_send_to_all(users, client);
    mx_free_request(&users);
}
