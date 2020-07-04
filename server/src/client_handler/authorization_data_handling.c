#include "api.h"

/*
 * Function: mx_correct_data
 * -------------------------------
 * Sends token to client if authorization data was valid
 * 
 * client: client that sent valid authorization data
 */
void mx_correct_data(t_client *client) {
    t_dtp *dtp = mx_token_request((char*)client->user->token,
                                  (char*)client->user->login,
                                  client->user->desc);

    mx_send(client->out, dtp);
    mx_logger(MX_LOG_FILE, G_LOG_LEVEL_MESSAGE, "Logged in correct");
    g_hash_table_insert(client->info->users, client->user->login,
                        client->out);
    mx_free_request(&dtp);
}

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

/*
 * Function: mx_valid_authorization_data
 * -------------------------------
 * Validates authorization data
 * 
 * data: authorization request
 * login: pointer to request login
 * pass: pointer to request password
 * client: client that sent this request
 * 
 * returns: success of validation
 */
gboolean mx_valid_authorization_data(t_dtp *data, char **login,
                                     char **pass, t_client *client) {
    if (client->user != NULL)
        return FALSE;
    if (!(*login = get_login_str(data)))
        return FALSE;
    if (!(*pass = get_pass_str(data)))
        return FALSE;
    return TRUE;
}
