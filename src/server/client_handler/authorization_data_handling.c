#include "server.h"
#include "protocol.h"

static char *get_login_str(t_dtp *data) {
    cJSON *data_obj = cJSON_GetObjectItemCaseSensitive(data->json, "login");

    if (!cJSON_IsString(data_obj))
        return NULL;
    if (!mx_match_search(data_obj->valuestring, MX_LOGIN_REGEX))
        return NULL;
    return data_obj->valuestring;
}

static char *get_pass_str(t_dtp *data) {
    cJSON *data_obj = cJSON_GetObjectItemCaseSensitive(data->json, "pass");

    if (!cJSON_IsString(data_obj))
        return NULL;
    if (!mx_match_search(data_obj->valuestring, MX_HASH_REGEX))
        return NULL;
    return data_obj->valuestring;
}

bool mx_valid_authorization_data(t_dtp *data, char **login, char **pass) {
    if (!data || data->type != MX_SIGN_UP)
        return false;
    if (!(*login = get_login_str(data)))
        return false;
    if (!(*pass = get_pass_str(data)))
        return false;
    return true;
}
