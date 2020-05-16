#include "server.h"

static void correct_data(const char *login, t_client *client) {
    t_dtp *dtp = mx_request_creation((char*)client->user->token);

    mx_send(client->ssl, dtp);
    mx_logger(MX_LOG_FILE, LOGMSG, "Logged in: %s\n", login);
    mx_free_request_struct(&dtp);
}

static void inccorect_data(t_client *client) {
    t_dtp *dtp = mx_request_creation("The token inccorect");

    mx_send(client->ssl, dtp);
    mx_free_request_struct(&dtp);
}

bool mx_log_in_token(t_dtp *token, t_client *client) {
    t_user *user = NULL;
    printf("token");

    if (token
        && (!mx_isvalid_hash(token->data))) {
        return false;
    }
    user = mx_get_user_by_token(token->data, client->chat->database);
    if (!user) {
        inccorect_data(client);
        mx_logger(MX_LOG_FILE, LOGWAR, "Inccorect token %s\n", token->data);
        return false;
    }
    client->user = user;
    mx_logger(MX_LOG_FILE, LOGMSG, "Connected by token %s\n", user->login);
    correct_data(user->login, client);
    return true;
}
