#include "server.h"

static void correct_data(char *login, t_client *client) {
    t_dtp *dtp = mx_log_in_token_request((char*)client->user->token);

    mx_send(client->ssl, dtp);
    mx_logger(MX_LOG_FILE, LOGMSG, "Logged in: %s\n", login);
    mx_free_request_struct(&dtp);
}

static void inccorect_data(t_client *client) {
    t_dtp *dtp = mx_error_msg_request(20, "The email or password inccorect");

    mx_send(client->ssl, dtp);
    mx_free_request_struct(&dtp);
}

static void log_in(char *login, char *pass, t_client *client) {
    t_user *user = mx_get_user_by_login(client->chat->database, login);

    if (!user) {
        // inccorect_data
        inccorect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "user not found %s\n", login);
    }
    else if (strcmp(user->password, pass)) {
        printf("%s\n%s\n", user->password, pass);
        inccorect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "Inccorect password %s\n", login);
    }
    else {
        client->user = user;
        correct_data(login, client);
    }
}

bool mx_log_in(t_dtp *login_data, t_client *client) {
    char md5_pass[MX_MD5_BUF_SIZE + 1];
    char *login_str;
    char *pass_str;

    if (!mx_valid_authorization_data(login_data, &login_str,
                                     &pass_str, MX_LOG_IN)) {
        return false;
    }
    mx_md5(md5_pass, (const unsigned char*)pass_str, strlen(pass_str));
    log_in(login_str, md5_pass, client);
    return true;
}
