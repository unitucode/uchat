/* protocol.h - Protocol of uchat
 * between client and server
 */
#pragma once

#include "utils.h"

#define MX_J_STR(m) (m) ? (m) : "(null)"
#define MX_MAX_FILE_SIZE 10000000
#define MX_FILES_DIR "files/"
#define MX_BUF_FILE 16384
#define MX_FILE_DELIM "__"
#define MX_MAX_ROOM_NAME 100
#define MX_MAX_MESSAGE 800

/* Protocol object
 * ----------
 * str: string request
 * json: json object of str
 * len: length of str
 * type: type of request
 */
typedef struct s_dtp t_dtp;

/* ERROR_TYPE
 * ----------
 * All types of errors in protocol
 */
typedef enum e_error_type {
    ER_AUTH_DATA = 0,
    ER_USER_EXST,
    ER_CLI_EXST,
    ER_COUNT_ERRS
}            t_error_type;

/* REQUEST_TYPE
 * ----------
 * All types of request in protocol
 */
typedef enum e_request_type {
    RQ_LOG_IN = 0,
    RQ_SIGN_UP,
    RQ_TOKEN,
    RQ_MSG,
    RQ_EDIT_MSG,
    RQ_DEL_MSG,
    RQ_DEL_HIST,
    RQ_GET_NEW_MSGS,
    RQ_SEARCH_MSG,
    RQ_ERROR_MSG,
    RQ_OLD_MSGS,
    RQ_GET_ROOMS,
    RQ_NEW_ROOM,
    RQ_DEL_ROOM,
    RQ_JOIN_ROOM,
    RQ_UPD_ROOM_NAME,
    RQ_UPD_ROOM_DESC,
    RQ_UPD_ROOM_POWR,
    RQ_SEARCH_CH,
    RQ_GET_MEMBERS,
    RQ_MEMBER_INFO,
    RQ_NEW_MEMBER,
    RQ_BAN_MEMBER,
    RQ_UPD_USER_DESC,
    RQ_UPLOAD_FILE,
    RQ_DOWNLOAD_FILE,
    RQ_LOG_OUT,
    RQ_READY_READ,
    RQ_COUNT_REQUEST
}            t_request_type;

/* ROOM_TYPE
 * ----------
 * All types of room
 */
typedef enum e_room_type {
    DB_PRIVAT_CHAT = 0,
    DB_GLOBAL_CHAT,
    DB_LS_CHAT
}            t_room_type;

/* MEMBER_TYPE
 * ----------
 * All types of member
 */
typedef enum e_member_type {
    DB_CUSTOMER = 0,
    DB_ADMIN,
    DB_MODERATOR,
    DB_SIMPLE,
    DB_BANNED
}            t_member_type;

/* MESSAGE_STATUS
 * ----------
 * All statuses of message
 */
typedef enum e_message_status {
    DB_MSG_START = 0,
    DB_MSG_EDIT,
}            t_message_status;

/* CONTACT_TYPE
 * ----------
 * All types of contacts
 */
typedef enum e_contact_type {
    DB_FRIENDS = 0,
    DB_BLACKLIST
}            t_contact_type;

/* MESSAGE_TYPE
 * ----------
 * All types of message
 */
typedef enum e_message_type {
    DB_TEXT_MSG = 0,
    DB_FILE_MSG,
    DB_FILE_TEXT_MSG,
    DB_STICKER
}            t_message_type;

struct s_dtp {
    char *str;
    cJSON *json;
    size_t len;
    gint type;
};

gboolean mx_isvalid_hash(char *hash);
gboolean mx_isvalid_login(char *login);
gboolean mx_isvalid_token(char *token);
void mx_create_token(char **token, char *login);

//Protocol
t_dtp *mx_get_transport_data(cJSON *json_result);
gint64 mx_get_type_dtp(t_dtp *dtp);
t_dtp *mx_request_creation(char *req_body);
void mx_free_request(t_dtp **request);
