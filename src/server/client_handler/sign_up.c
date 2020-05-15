#include "server.h"
#include "protocol.h"

static void inccorect_data(t_client *client) {
    t_dtp *dtp = mx_request_creation("User with this name is already exist");

    mx_send(client->ssl, dtp);
    mx_free_request_struct(&dtp);
}

static void correct_data(t_client *client) {
    t_dtp *dtp = mx_request_creation((char*)client->user->token);

    mx_send(client->ssl, dtp);
    mx_free_request_struct(&dtp);
}

static void sign_up(t_dtp *login, char *pass, t_client *client) {
    t_user *user = mx_get_user_by_login(login->data, client->chat->database);
    char token[MX_MD5_BUF_SIZE + 1];

    if (user) {
        inccorect_data(client);
        mx_delete_user(&user);
        mx_logger(MX_LOG_FILE, LOGMSG, "Already exist user %s\n",
                  login->data);
        return;
    }
    mx_create_token(token, login->data);
    client->user = mx_insert_user(login->data, pass, token,
                                  client->chat->database);
    correct_data(client);
}

bool mx_sign_up(t_dtp *login, t_client *client) {
    t_dtp *pass = NULL;
    char md5_pass[MX_MD5_BUF_SIZE + 1];

    if (login
        && (!mx_isvalid_login(login->data))) {
        return false;
    }
    pass = mx_recv(client->ssl);
    if (pass && (!mx_isvalid_hash(pass->data))) {
        mx_logger(MX_LOG_FILE, LOGWAR,
                  "First packet was login(%s), but second wasn`t pass\n",
                  login->data);
        return false;
    }
    mx_md5(md5_pass, (const unsigned char*)pass->data, pass->len);
    sign_up(login, md5_pass, client);
    return true;
}
