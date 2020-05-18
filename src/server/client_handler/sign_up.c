#include "server.h"
#include "protocol.h"

static void sign_up(char *login, char *pass, t_client *client) {
    t_user *user = mx_get_user_by_login(client->chat->database, login);
    char token[MX_MD5_BUF_SIZE + 1];

    if (user) {
        // inccorect_data
        mx_delete_user(client->chat->database, login);
        mx_logger(MX_LOG_FILE, LOGMSG, "Already exist user %s\n", login);
        return;
    }
    mx_create_token(token, login);
    client->user = mx_insert_user(client->chat->database,
                                  login, pass, token);
    // correct_data
}

static char *get_login_str(t_dtp *signup_data) {
    cJSON *data_obj = cJSON_GetObjectItemCaseSensitive(signup_data->json,
                                                       "login");
    if (!cJSON_IsString(data_obj))
        return NULL;
    if (!mx_match_search(data_obj->valuestring, MX_LOGIN_REGEX))
        return NULL;
    return data_obj->valuestring;
}

static char *get_pass_str(t_dtp *signup_data) {
    cJSON *data_obj = cJSON_GetObjectItemCaseSensitive(signup_data->json,
                                                       "pass");
    if (!cJSON_IsString(data_obj))
        return NULL;
    if (!mx_match_search(data_obj->valuestring, MX_HASH_REGEX))
        return NULL;
    return data_obj->valuestring;
}

bool mx_sign_up(t_dtp *signup_data, t_client *client) {
    char md5_pass[MX_MD5_BUF_SIZE + 1];
    char *login_str;
    char *pass_str;

    if (!signup_data || signup_data->type != MX_SIGN_UP)
        return false;
    if (!(login_str = get_login_str(signup_data)))
        return false;
    if (!(pass_str = get_pass_str(signup_data)))
        return false;
    mx_md5(md5_pass, (const unsigned char *)pass_str, strlen(pass_str));
    sign_up(login_str, md5_pass, client);
    return true;
}
