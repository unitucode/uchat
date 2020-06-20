#include "server.h"
#include "protocol.h"

static void incorrect_data(t_client *client) {
    t_dtp *dtp = mx_error_msg_request(ER_USER_EXST, "User already exist");

    mx_send(client->out, dtp);
    mx_free_request(&dtp);
}

static bool sign_up(t_db_user *user, t_client *client) {
    t_db_user *check_user = mx_get_user_by_login(client->info->database, user->login);
    char token[MX_MD5_BUF_SIZE + 1 + strlen(user->login)];

    if (check_user) {
        incorrect_data(client);
        mx_free_user(&check_user);
        mx_logger(MX_LOG_FILE, LOGMSG, "Already exist user %s\n", user->login);
        return false;
    }
    mx_create_token(token, user->login);
    user->token = strdup(token);
    mx_insert_user_into_db(client->info->database, user);
    mx_logger(MX_LOG_FILE, LOGMSG, "Success signup user %s\n", user->login);
    client->user = user;
    mx_correct_data(user->login, client);
    return true;
}

bool mx_sign_up_handler(t_dtp *signup_data, t_client *client) {
    t_db_user *user = mx_parse_json_user(signup_data->json);

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
    if (!sign_up(user, client)) {
        mx_free_user(&user);
        return false;
    }
    return true;
}
