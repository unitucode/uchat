#include "server.h"

bool mx_log_in_token(t_pdl *token, t_client *client) {
    t_user *user = NULL;

    if (token
        && (token->type != MX_TOKEN_AUTH || !mx_isvalid_hash(token->data))) {
        return false;
    }
    user = mx_get_user_on_token(token->data, client->chat->database);
    if (!user) {
        mx_logger(MX_LOG_FILE, LOGWAR, "Inccorect token %s\n", token->data);
        return false;
    }
    client->user = user;
    mx_logger(MX_LOG_FILE, LOGMSG, "Connected by token %s\n", user->login);
    return true;
}
