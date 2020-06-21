#pragma once

#include "utils.h"

#define MX_J_STR(m) (m) ? (m) : "(null)"
#define MX_MAX_FILE_SIZE 50000000

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
    RQ_SEARCH_CH,
    RQ_JOIN_ROOM,
    RQ_GET_MEMBERS,
    RQ_COUNT_REQUEST,
}            t_request_type;

typedef enum s_room_type {
    DB_PRIVAT_CHAT = 0,
    DB_GLOBAL_CHAT,
    DB_LS_CHAT
}            t_room_type;

typedef enum s_message_type {
    DB_STATUS_MSG_START = 0,
    DB_STATUS_MSG_EDIT
}            t_message_type;

struct s_file {
    char *bytes;
    char *name;
    struct stat st;
};

struct s_dtp { // Data Transfer Protocol view
    char *str;
    cJSON *json;
    size_t len;
    int type;
};


//requests
t_dtp *mx_delete_room_request(char *room_name);
t_dtp *mx_get_transport_data(cJSON *json_result);

//SSL
bool mx_isvalid_hash(char *hash);
bool mx_isvalid_login(char *login);
bool mx_isvalid_token(char *token);
void mx_create_token(char **token, char *login);

//Protocol
int mx_get_type_dtp(t_dtp *dtp);
t_dtp *mx_request_creation(char *req_body);
void mx_free_request(t_dtp **request);
