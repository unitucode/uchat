#include "server.h"

static void inccorect_data(t_client *client) {
    t_pds *pds = mx_request_creation(-1, MX_ERR_MSG,
                                     "User with this name is already exist");

    mx_send(client->ssl, pds);
    mx_free_request_struct(&pds);
}

static void correct_data(t_client *client) {
    t_pds *pds = mx_request_creation(-1, MX_TOKEN_AUTH,
                                     (char*)client->user->token);

    mx_send(client->ssl, pds);
    mx_free_request_struct(&pds);
}

static void sign_up(t_pdl *login, char *pass, t_client *client) {
    t_user *user = mx_get_user(login->data, client->chat->database);
    char token[MX_MD5_BUF_SIZE + 1];
    char seed[login->len + strlen(pass) + 1];

    if (user) {
        inccorect_data(client);
        mx_delete_user(&user);
        mx_logger(MX_LOG_FILE, LOGMSG, "Already exist user %s\n",
                  login->data);
        return;
    }
    bzero(seed, sizeof(seed));
    strcpy(seed, login->data);
    strcat(seed, pass);
    mx_md5(token, (const unsigned char*)seed, sizeof(seed));
    client->user = mx_insert_user(login->data, pass, token,
                                  client->chat->database);
    correct_data(client);
}

bool mx_sign_up(t_pdl *login, t_client *client) {
    t_pdl *pass = NULL;
    char md5_pass[MX_MD5_BUF_SIZE + 1];

    if (login && login->type != MX_SIGN_UP) 
        return false;
    pass = mx_recv(client->ssl);
    if (pass && (pass->type != MX_PASSWORD || mx_isvalid_hash(pass->data))) {
        mx_free_decode_struct(&pass);
        mx_logger(MX_LOG_FILE, LOGWAR,
                  "First packet was login(%s), but second wasn`t pass\n",
                  login->data);
        return false;
    }
    mx_md5(md5_pass, (const unsigned char*)pass->data, pass->len);
    sign_up(login, md5_pass, client);
    return true;
}
