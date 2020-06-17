#include "server.h"
#include "protocol.h"

static void incorrect_data(t_client *client) {
    t_dtp *dtp = mx_error_msg_request(ER_AUTH_DATA, "The email or password inccorect");

    mx_send(client->ssl, dtp);
    mx_free_request(&dtp);
}

static void log_in(char *login, char *pass, t_client *client) {
    t_db_user *user = mx_get_user_by_login(client->chat->database, login);

    if (!user) {
        incorrect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "user not found %s\n", login);
    }
    else if (strcmp(user->pass, pass)) {
        printf("%s\n%s\n", user->pass, pass);
        incorrect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "Inccorect password %s\n", login);
        mx_free_user(&user);
    }
    else {
        client->user = user;
        mx_correct_data(login, client);
    }
}

bool mx_log_in_handler(t_dtp *login_data, t_client *client) {
    char md5_pass[MX_MD5_BUF_SIZE + 1];
    char *login_str;
    char *pass_str;

    if (!mx_valid_authorization_data(login_data, &login_str,
                                     &pass_str, client)) {
        return false;
    }
    mx_md5(md5_pass, (const unsigned char*)pass_str, strlen(pass_str));
    log_in(login_str, md5_pass, client);
    return true;
}
