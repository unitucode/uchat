#include "api.h"

static void incorrect_data(t_client *client) {
    t_dtp *dtp = mx_error_msg_request(ER_AUTH_DATA, "The email or password inccorect");

    mx_send(client->out, dtp);
    mx_free_request(&dtp);
}

/*
 * Function: log_in
 * -------------------------------
 * Validates authorization data
 * 
 * user: user in database
 * client: client that sent request
 * 
 * returns: success of loging
 */
static bool log_in(t_db_user *user, t_client *client) {
    t_db_user *check_user = mx_get_user_by_login(client->info->database, user->login);

    if (!check_user) {
        incorrect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "user not found %s\n", user->login);
        return true;
    }
    else if (strcmp(check_user->pass, user->pass)) {
        incorrect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "Inccorect password %s\n", user->login);
        mx_free_user(&check_user);
        return true;
    }
    client->user = check_user;
    mx_correct_data(client);
    return true;
}

/*
 * Function: mx_log_in_handler
 * -------------------------------
 * Handles request from client
 * 
 * room: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
bool mx_log_in_handler(t_dtp *login_data, t_client *client) { //ADD ENCRYPT
    t_db_user *user = mx_parse_json_user(login_data->json);

    if (!user)
        return false;
    if (!mx_match_search(user->login, MX_LOGIN_REGEX)) {
        mx_free_user(&user);
        return false;
    }
    if (!mx_match_search(user->pass, MX_HASH_REGEX)) {
        mx_free_user(&user);
        return false;
    }
    if (!log_in(user, client)) {
        mx_free_user(&user);
        return false;
    }
    mx_free_user(&user);
    return true;
}
