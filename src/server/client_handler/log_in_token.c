#include "server.h"

static void correct_data(const char *login, t_client *client) {
    t_pds *pds = mx_request_creation(-1, MX_TOKEN_AUTH,
                                     (char*)client->user->token);

    mx_send(client->ssl, pds);
    mx_logger(MX_LOG_FILE, LOGMSG, "Logged in: %s\n", login);
    mx_free_request_struct(&pds);
}

static void inccorect_data(t_client *client) {
    t_pds *pds = mx_request_creation(-1, MX_ERR_MSG, "The token inccorect");

    mx_send(client->ssl, pds);
    mx_free_request_struct(&pds);
}

bool mx_log_in_token(t_pdl *token, t_client *client) {
    t_user *user = NULL;
    printf("token");

    if (token
        && (token->type != MX_TOKEN_AUTH || !mx_isvalid_hash(token->data))) {
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
