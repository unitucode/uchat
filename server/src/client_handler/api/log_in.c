#include "api.h"

static void incorrect_data(t_client *client) {
    t_dtp *dtp = mx_error_msg_request(ER_AUTH_DATA,
                                      "The email or password inccorect");

    mx_send(client->out, dtp);
    mx_free_request(&dtp);
}

static void exist_client(t_client *client) {
    t_dtp *dtp = mx_error_msg_request(ER_CLI_EXST, "User already authorized");

    mx_send(client->out, dtp);
    mx_free_request(&dtp);
}

static gboolean check_user(t_db_user *check, t_db_user *user,
                           t_client *client) {
    if (!check) {
        incorrect_data(client);
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_MESSAGE, "user not found");
        mx_free_user(&check);
        return FALSE;
    }
    else if (g_strcmp0(check->pass, user->pass)) {
        incorrect_data(client);
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_MESSAGE, "Inccorect pass");
        mx_free_user(&check);
        return FALSE;
    }
    else if (g_hash_table_lookup(client->info->users, check->login)) {
        exist_client(client);
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_MESSAGE, "Already online");
        mx_free_user(&check);
        return FALSE;
    }
    return TRUE;
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
static gboolean log_in(t_db_user *user, t_client *client) {
    t_db_user *check = mx_get_user_by_login(client->info->database,
                                                 user->login);
    if (!check_user(check, user, client))
        return TRUE;
    client->user = check;
    mx_correct_data(client);
    return TRUE;
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
gboolean mx_log_in_handler(t_dtp *login_data, t_client *client) {
    t_db_user *user = mx_parse_json_user(login_data->json);

    if (!user)
        return FALSE;
    if (!mx_match_search(user->login, MX_LOGIN_REGEX)) {
        mx_free_user(&user);
        return FALSE;
    }
    if (!mx_match_search(user->pass, MX_HASH_REGEX)) {
        mx_free_user(&user);
        return FALSE;
    }
    if (!log_in(user, client)) {
        mx_free_user(&user);
        return FALSE;
    }
    mx_free_user(&user);
    return TRUE;
}
