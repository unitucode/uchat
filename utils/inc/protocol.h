#pragma once

#include "utils.h"

#define MX_J_STR(m) (m) ? (m) : "(null)"
#define MX_RQ_SIZE 2048
#define MX_MAX_FILE_SIZE 50000000
#define MX_RES_OK "OK"
#define MX_READY "READY"

typedef struct s_ssl_con t_ssl_con;
typedef struct s_dtp t_dtp;
typedef struct s_file t_file;

typedef enum s_error_type {
    ER_AUTH_DATA = 0,
    ER_USER_EXST,
    ER_COUNT_ERRS
}            t_error_type;

typedef enum s_request_type {
    RQ_LOG_IN = 0,
    RQ_SIGN_UP,
    RQ_LOG_OUT,
    RQ_TOKEN,
    RQ_MSG,
    RQ_NEW_ROOM,
    RQ_DELETE_ROOM,
    RQ_ERROR_MSG,
    RQ_USERS_ONLINE,
    RQ_GET_ROOMS,
    RQ_GET_NEW_MSGS,
    RQ_UPD_ROOM_DESC,
    RQ_UPD_ROOM_NAME,
    RQ_UPD_USER_DESC,
    RQ_UPD_USER_NAME,
    RQ_RECONNECT,
    RQ_DEL_ROOM,
    RQ_DEL_USER,
    RQ_EDIT_MSG,
    RQ_DEL_MSG,
    RQ_FILE,
    RQ_READY,
    RQ_COUNT_REQUEST
}            t_request_type;

struct s_file {
    char *bytes;
    char *name;
    struct stat st;
};

struct s_ssl_con {
    SSL_CTX *ctx;
    SSL *ssl;
    char *cert_file;
    char *key_file;
    char *password;
};

struct s_dtp { // Data Transfer Protocol view
    char *data;
    char *str;
    cJSON *json;
    size_t len;
    int type;
};

//file transfer
t_file *mx_upload_file(char *file_path);
char *mx_recv_file(SSL *ssl, size_t size);
int mx_send_file(SSL *ssl, char *data_bytes, size_t size);
void mx_free_file(t_file **file);

//requests
t_dtp *mx_delete_room_request(char *room_name);
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
