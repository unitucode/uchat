#pragma once

#include "utils.h"

#define MX_J_STR(m) (m) ? (m) : "(null)"

typedef enum s_request_type {
    RQ_LOG_IN = 0,
    RQ_SIGN_UP,
    RQ_TOKEN,
    RQ_MSG,
    RQ_NEW_ROOM,
    RQ_DELETE_ROOM,
    RQ_ERROR_MSG,
    RQ_COUNT_REQUEST
}            t_request_type;

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
    cJSON *json;
    size_t len;
    int type;
}              t_dtp;

//requests
t_dtp *mx_log_in_request(char *login, char *pass);
t_dtp *mx_sign_up_request(char *login, char *pass);
t_dtp *mx_log_in_token_request(char *token);
t_dtp *mx_msg_request(int id_room, char *from, char *msg);
t_dtp *mx_new_room_request(char *room_name, bool is_private, char *pass);
t_dtp *mx_delete_room_request(char *room_name);
t_dtp *mx_error_msg_request(int error_code, char *msg);
t_dtp *mx_token_request(char *token);
t_dtp *mx_get_transport_data(cJSON *json_result);

//SSL
t_ssl_con *mx_init_ssl(t_app_type type);
void mx_md5(char *buf, const unsigned char *str, size_t len);
bool mx_isvalid_hash(char *hash);
bool mx_isvalid_login(char *login);
bool mx_isvalid_token(char *token);
void mx_create_token(char *token, char *login);

//Protocol
int mx_get_type_dtp(t_dtp *dtp);
t_dtp *mx_request_creation(char *req_body);
void mx_free_request(t_dtp **request);
