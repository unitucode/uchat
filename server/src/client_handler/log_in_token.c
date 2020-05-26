#include "server.h"

bool mx_log_in_token(t_dtp *token, t_client *client) {
    cJSON *obj = NULL;
    t_user *user = NULL;

    if (!token || token->type != MX_TOKEN)
        return false;
    obj = cJSON_GetObjectItemCaseSensitive(token->json, "token");
    if (!cJSON_IsString(obj))
        return false;
    if (!mx_isvalid_token(obj->valuestring))
        return false;
    user = mx_get_user_by_token(client->chat->database, obj->valuestring);
    if (!user) {
        mx_logger(MX_LOG_FILE, LOGERR, "No users with this token: %s",
                 obj->valuestring);
        return false;
    }
    return true;
}
