#pragma once

#include "utils.h"



#define MX_LOG_IN 0
#define MX_SIGN_UP 1
#define MX_TOKEN 2
#define MX_MSG 3

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

//requests
t_dtp *mx_log_in_request(char *login, char *pass);
t_dtp *mx_sign_up_request(char *login, char *pass);
t_dtp *mx_log_in_token_request(char *token);
t_dtp *mx_msg_request(int id_room, char *from, char *msg);

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
