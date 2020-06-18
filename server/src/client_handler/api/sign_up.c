#include "server.h"
#include "protocol.h"

static void incorrect_data(t_client *client) {
    t_dtp *dtp = mx_error_msg_request(ER_USER_EXST, "User already exist");

    mx_send(client->ssl, dtp);
    mx_free_request(&dtp);
}

static void sign_up(char *login, char *pass, t_client *client) {
    t_db_user *user = mx_get_user_by_login(client->chat->database, login);
    char token[MX_MD5_BUF_SIZE + 1 + strlen(login)];
pass++;
    if (user) {
        incorrect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "Already exist user %s\n", login);
        return;
    }
    mx_create_token(token, login);
    // client->user = mx_insert_user_into_db(client->chat->database, login, pass, token);
    if (!client->user) {
        mx_logger(MX_LOG_FILE, LOGMSG, "Failded signup user %s\n", login);
        return;
    }
    mx_logger(MX_LOG_FILE, LOGMSG, "Success signup user %s\n", login);
    mx_correct_data(login, client);
    return;
}

bool mx_sign_up_handler(t_dtp *signup_data, t_client *client) {
    char md5_pass[MX_MD5_BUF_SIZE + 1];
    char *login_str;
    char *pass_str;

    if (!mx_valid_authorization_data(signup_data, &login_str,
                                     &pass_str, client)) {
        return false;
    }
    mx_md5(md5_pass, (const unsigned char*)pass_str, strlen(pass_str));
    sign_up(login_str, md5_pass, client);
    return true;
}
