#include "client.h"

bool mx_authorization(t_dtp *token, t_chat *chat) {
    cJSON *json = NULL;
    cJSON *auth_token = NULL;

    if (token->type != MX_TOKEN && !chat->auth_token) {
        return false;
    }
    json = cJSON_Parse(token->str);
    auth_token = cJSON_GetObjectItemCaseSensitive(token->json, "token");
    if (!cJSON_IsString(auth_token)
        || !mx_isvalid_token(auth_token->valuestring)) {
            return false;
    }
    chat->auth_token = auth_token->valuestring;
    return true;
}
