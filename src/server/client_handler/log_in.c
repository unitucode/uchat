#include "server.h"

static void correct_data(t_pdl *login, t_client *client) {
    t_pds *pds = mx_request_creation(-1, MX_TOKEN_AUTH,
                                     (char*)client->user->token);

    mx_send(client->ssl, pds);
    mx_logger(MX_LOG_FILE, LOGMSG, "Logged in: %s\n", login->data);
    mx_free_request_struct(&pds);
}

static void inccorect_data(t_client *client) {
    t_pds *pds = mx_request_creation(-1, MX_ERR_MSG,
                                     "The email or password inccorect");

    mx_send(client->ssl, pds);
    mx_free_request_struct(&pds);
}

static void log_in(t_pdl *login, t_pdl *pass, t_client *client) {
    t_user *user = mx_get_user_on_login(login->data, client->chat->database);

    if (!user) {
        inccorect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "Non-existent user %s\n", login->data);
    }
    else if (strcmp(user->password, pass->data)) {
        inccorect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "Inccorect password %s\n",
                  login->data);
        mx_delete_user(&user);
    }
    else {
        client->user = user;
        correct_data(login, client);
    }
}

bool mx_log_in(t_pdl *login, t_client *client) {
    t_pdl *pass = NULL;

    if (login && login->type != MX_LOG_IN)
        return false;
    pass = mx_recv(client->ssl);
    if (pass && pass->type != MX_PASSWORD) {
        mx_free_decode_struct(&pass);
        mx_logger(MX_LOG_FILE, LOGWAR,
                  "First packet was login(%s), but second wasn`t pass\n",
                  login->data);
        return false;
    }
    log_in(login, pass, client);
    mx_free_decode_struct(&pass);
    return true;
}
