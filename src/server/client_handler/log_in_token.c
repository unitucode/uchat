#include "server.h"

static bool check_token(char *token) {
    bool retval = true;
    char *hash = NULL;      // Replace for new mx_match_n_search

    if (strlen(token) < 35)
        return false;
    hash = strndup(token, 32);
    if (!mx_match_search(hash, MX_HASH_REGEX)
        || !mx_match_search(token + 32, MX_LOGIN_REGEX)) {
        retval = false;
    }
    mx_free((void**)&hash);     // Replace for new mx_match_n_search
    return retval;
}

bool mx_log_in_token(t_dtp *token, t_client *client) {
    cJSON *obj = NULL;
    t_user *user = NULL;

    if (!token || token->type != MX_TOKEN)
        return false;
    obj = cJSON_GetObjectItemCaseSensitive(token->json, "token");
    if (!cJSON_IsString(obj))
        return false;
    if (!check_token(obj->valuestring))
        return false;
    user = mx_get_user_by_token(client->chat->database, obj->valuestring);
    if (!user) {
        mx_logger(MX_LOG_FILE, LOGERR, "No users with this token: %s",
                 obj->valuestring);
        return false;
    }
    return true;
}
