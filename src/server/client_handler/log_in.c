#include "server.h"

static void correct_data(t_dtp *login_data, t_client *client) {
    t_dtp *dtp = mx_request_creation((char*)client->user->token);

    mx_send(client->ssl, dtp);
    mx_logger(MX_LOG_FILE, LOGMSG, "Logged in: %s\n", login_data->data);
    mx_free_request_struct(&dtp);
}

static void inccorect_data(t_client *client) {
    t_dtp *dtp = mx_request_creation("The email or password inccorect");

    mx_send(client->ssl, dtp);
    mx_free_request_struct(&dtp);
}

static void log_in(char *login, char *pass, t_client *client,
                   t_dtp *login_data) {
    t_user *user = mx_get_user_by_login(client->chat->database, login);

    if (!user) {
        // inccorect_data
        inccorect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "user not found %s\n", login);
    }
    else if (strcmp(user->password, pass)) {
        inccorect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "Inccorect password %s\n", login);
        mx_delete_user(client->chat->database, login);
    }
    else {
        client->user = user;
        correct_data(login_data, client);
    }
}

bool mx_log_in(t_dtp *login_data, t_client *client) {
    char *login_str;
    char *pass_str;

    if (!mx_valid_authorization_data(login_data, &login_str, &pass_str))
        return false;
    log_in(login_str, pass_str, client, login_data);
    return true;
}
