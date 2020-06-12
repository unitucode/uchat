#include "server.h"

t_dtp *mx_log_out_request(char *token) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_LOG_OUT))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "token", token))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_log_out_handler(t_dtp *token, t_client *client) {
    cJSON *tok = cJSON_GetObjectItemCaseSensitive(token->json, "token");
    t_dtp *answer = NULL;

    if (!tok || !cJSON_IsString(tok) || !mx_isvalid_token(tok->valuestring))
        return false;
    if (strcmp(client->user->token, tok->valuestring))
        return false;
    answer = mx_log_out_request((char*)client->user->token);
    mx_free_user(&client->user);
    mx_send(client->ssl, answer);
    mx_update_online(--client->chat->online_users, client);
    mx_free_request(&answer);
    return true;
}
