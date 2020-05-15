#pragma once

#include "utils.h"


typedef struct s_ssl_con {
    SSL_CTX *ctx;
    SSL *ssl;
    char *cert_file;
    char *key_file;
    char *password;
}              t_ssl_con;

typedef enum e_request_types {
    MX_LOG_IN = 0, //+
    MX_PASSWORD = 1, //+
    MX_USER_COUNT = 2,
    MX_MESSAGE = 3,
    MX_FILE = 4,
    MX_SIZE_MSG = 5,
    MX_ERR_MSG = 6,
    MX_TOKEN_AUTH = 7,
    MX_SIGN_UP
}            t_request_types;

typedef struct s_dtp { // Data Transfer Protocol view
    char *data;
    char *str;
    size_t len;
}              t_dtp;

//SSL
t_ssl_con *mx_init_ssl(t_app_type type);
t_dtp *mx_recv(SSL *ssl);
int mx_send(SSL *ssl, t_dtp *data);
void mx_md5(char *buf, const unsigned char *str, size_t len);
bool mx_isvalid_hash(char *hash);
bool mx_isvalid_login(char *login);
bool mx_isvalid_token(char *token);
void mx_create_token(char *token, char *login);

//Protocol
t_dtp *mx_request_creation(char *req_body);
void mx_free_request_struct(t_dtp **request);
