#include "server.h"

t_dtp *mx_token_request(char *token, char *login) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_TOKEN))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "token", MX_J_STR(token)))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "login", login))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_log_in_token_handler(t_dtp *token, t_client *client) { // TODO!!!!!!
    cJSON *json = cJSON_Parse(token->str);
    cJSON *user_token = cJSON_GetObjectItemCaseSensitive(json, "token");

    if (user_token && cJSON_IsString(user_token)
        && mx_isvalid_token(user_token->valuestring)) {
        client->user = mx_get_user_by_token(client->chat->database,
                                            user_token->valuestring);
    }
    if (!client->user) {
        mx_logger(MX_LOG_FILE, LOGWAR, "Inccorect token\n");
        cJSON_Delete(json);
        return false;
    }
    cJSON_Delete(json);
    mx_logger(MX_LOG_FILE, LOGMSG, "Logged by token %s\n", client->user->name);
    mx_send(client->ssl, token);
    return true;
}
