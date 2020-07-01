#include "api.h"

static void incorrect_data(t_client *client) {
    t_dtp *dtp = mx_error_msg_request(ER_USER_EXST, "User already exist");

    mx_send(client->out, dtp);
    mx_free_request(&dtp);
}

/*
 * Function: sign_up
 * -------------------------------
 * Validate sign up data
 * 
 * user: information about user in database
 * client: client that sent sign up request
 * 
 * returns: success of validation
 */
static gboolean sign_up(t_db_user *user, t_client *client) {
    char *token;

    if (mx_check_user_by_login(client->info->database, user->login)) {
        incorrect_data(client);
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_MESSAGE, "Already exist user");
        return FALSE;
    }
    mx_create_token(&token, user->login);
    user->token = token;
    mx_insert_user_into_db(client->info->database, user);
    mx_logger(MX_LOG_FILE, G_LOG_LEVEL_MESSAGE, "Success signup user");
    client->user = user;
    mx_correct_data(client);
    return TRUE;
}

/*
 * Function: mx_sign_up_handler
 * -------------------------------
 * Handles request from client
 * 
 * signup_data: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_sign_up_handler(t_dtp *signup_data, t_client *client) {
    t_db_user *user = mx_parse_json_user(signup_data->json);

    if (!user) {
        return FALSE;
    }
    if (!mx_match_search(user->login, MX_LOGIN_REGEX)) {
        mx_free_user(&user);
        return FALSE;
    }
    if (!mx_match_search(user->pass, MX_HASH_REGEX)) {
        mx_free_user(&user);
        return FALSE;
    }
    if (!sign_up(user, client))
        mx_free_user(&user);
    return TRUE;
}
