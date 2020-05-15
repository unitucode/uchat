#include "server.h"

static void correct_data(t_pdl *login, t_client *client) {
    t_dtp *dtp = mx_request_creation((char*)client->user->token);

    mx_send(client->ssl, dtp);
    mx_logger(MX_LOG_FILE, LOGMSG, "Logged in: %s\n", login->data);
    mx_free_request_struct(&dtp);
}

static void inccorect_data(t_client *client) {
    t_dtp *dtp = mx_request_creation("The email or password inccorect");

    mx_send(client->ssl, dtp);
    mx_free_request_struct(&dtp);
}

static void log_in(t_pdl *login, char *pass, t_client *client) {
    t_user *user = mx_get_user_by_login(login->data, client->chat->database);

    if (!user) {
        inccorect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "Non-existent user %s\n", login->data);
    }
    else if (strcmp(user->password, pass)) {
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
    char md5_pass[MX_MD5_BUF_SIZE + 1];

    if (login && (login->type != MX_LOG_IN || !mx_isvalid_login(login->data)))
        return false;
    pass = mx_recv(client->ssl);
    if (pass
        && (pass->type != MX_PASSWORD || !mx_isvalid_hash(pass->data))) {
        mx_free_decode_struct(&pass);
        mx_logger(MX_LOG_FILE, LOGWAR,
                  "First packet was login(%s), but second wasn`t pass\n",
                  login->data);
        return false;
    }
    mx_md5(md5_pass, (const unsigned char*)pass->data, pass->len);
    log_in(login, md5_pass, client);
    mx_free_decode_struct(&pass);
    return true;
}
