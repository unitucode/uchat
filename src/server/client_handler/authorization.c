#include "server.h"

void mx_create_token(char *token, char *login) {
    char seed[MX_MD5_BUF_SIZE + 1];

    bzero(token, MX_MD5_BUF_SIZE + 1);
    bzero(seed, MX_MD5_BUF_SIZE + 1);
    mx_randomize_str(seed, MX_MD5_BUF_SIZE);
    mx_md5(token, (const unsigned char*)seed, sizeof(seed));
    strcat(token, login);
}

bool mx_authorization(t_client *client, t_pdl *data) {
    return client->user
           || mx_log_in(data, client)
           || mx_sign_up(data, client)
           || mx_log_in_token(data, client);
}
