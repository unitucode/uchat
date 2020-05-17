#pragma once

#include "utils.h"

#define MX_TP_LOG_IN "{type: "MX_ITOA(MX_LOG_IN)", login: %s, pass: %s}"
#define MX_TP_SIGN_UP "{type: "MX_ITOA(MX_SIGN_UP)", login: %s, pass: %s}"
#define MX_TP_MSG "{type: "MX_ITOA(MX_MSG)", from: %s, msg: %s}"

#define MX_LOG_IN 0
#define MX_SIGN_UP 1
#define MX_MSG 2

typedef struct s_ssl_con {
    SSL_CTX *ctx;
    SSL *ssl;
    char *cert_file;
    char *key_file;
    char *password;
}              t_ssl_con;

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
t_dtp *mx_request_json(const char *fmt, ...);
t_dtp *mx_request_creation(char *req_body);
void mx_free_request_struct(t_dtp **request);
