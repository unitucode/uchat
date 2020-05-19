#include "server.h"

bool mx_log_in_token(t_dtp *token, t_client *client) {
    cJSON *obj = NULL;
    t_user *user = NULL;

    if (!token || toket->type != MX_TOKEN)
        return false;
    obj = cJSON_GetObjectItemCaseSensitive(token->json, "token");
    if (!cJSON_IsString(obj))
        return false;
    if (!mx_match_search(obj->valuestring, MX_HASH_REGEX))
        return false;
    user = mx_get_user_by_token(client->user->database, obj->valuestring);
    if (!user) {
        mx_loger(MX_LOG_FILE, LOGERR, "No users with this token: %s",
                 obj->valuestring);
        return false;
    }
    return true;
}
