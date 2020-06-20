#pragma once

#include "utils.h"
#include "protocol.h"
#include "list.h"
#include "sqlite3.h"
#include "database.h"
#include <glib.h>
#include <gio/gio.h>

//settings
#define MX_LISTENQ 1024
#define MX_PORT_LEN 8
#define MX_REQUEST_PER_SECOND 20
#define MX_DELAY (1000000 / MX_REQUEST_PER_SECOND)
#define MX_MAX_ROOMS 20
#define MX_MAX_MSGS 500

typedef struct s_chat t_chat;
typedef struct s_client t_client;
typedef struct s_info t_info;
typedef struct s_send_helper t_send_helper;

struct s_info {
    GHashTable *users;
    sqlite3* database;
    bool (*request_handler[RQ_COUNT_REQUEST])(t_dtp *dtp, t_client *chat);
};

struct s_client {
    GSocketConnection *conn;
    GDataOutputStream *out;
    GDataInputStream *in;
    GInputStream *in_s;
    char *msg;
    t_db_user *user;
    t_info *info;
};

struct s_send_helper {
    GHashTable *table;
    t_dtp *data;
};

gssize mx_send(GDataOutputStream *out, t_dtp *dtp);
bool mx_handle_request(char *request, t_client *client);

//api
t_dtp *mx_token_request(char *token, char *login);
t_dtp *mx_error_msg_request(int error_code, char *msg);
t_dtp *mx_users_online_request(int count, int all);
t_dtp *mx_log_out_request(char *token);
t_dtp *mx_upd_room_desc_request(int room_id, char *room_name);
t_dtp *mx_upd_room_name_request(int room_id, char *room_name);
t_dtp *mx_upd_user_desc_request(char *name, char *desc);
t_dtp *mx_reconnect_request(char *token, char *login);

//data protocol handler functions
bool mx_log_in_handler(t_dtp *login, t_client *client);
bool mx_sign_up_handler(t_dtp *signup_data, t_client *client);
bool mx_log_in_token_handler(t_dtp *token, t_client *client);
bool mx_new_room_handler(t_dtp *data, t_client *client);
bool mx_msg_handler(t_dtp *data, t_client *client);
bool mx_get_rooms_handler(t_dtp *data, t_client *client);
bool mx_log_out_handler(t_dtp *token, t_client *client);
bool mx_get_msgs_handler(t_dtp *data, t_client *client);
bool mx_upd_room_desc_handler(t_dtp *desc, t_client *client); //TODO
bool mx_upd_room_name_handler(t_dtp *desc, t_client *client); //TODO
bool mx_upd_user_desc_handler(t_dtp *desc_data, t_client *client); //TODO
bool mx_del_room_handler(t_dtp *data, t_client *client); //TODO
bool mx_del_msg_handler(t_dtp *msg, t_client *client); //TODO
bool mx_edit_msg_handler(t_dtp *msg, t_client *client); //TODO!!!!!!! DB
bool mx_upload_file_handler(t_dtp *data, t_client *client); //TODO

t_info *mx_init_info(void);
void mx_deinit_info(t_info **info);
void mx_init_receiver(t_info *chat);

int mx_tcp_listen(const char *serv, socklen_t *addr_len);
void mx_get_client_info(t_client *client);
t_client *mx_new_client(socklen_t len);
void mx_connect_client(t_client *client);
void mx_disconnect_client(t_client *client);
void mx_delete_client(void **client);
void *mx_receiver(void *arg);
void mx_send_to_all(t_dtp *data, t_client *client, guint64 room_id);
void mx_update_online(int count, t_client *client);

//Authorization
bool mx_valid_authorization_data(t_dtp *data, char **login,
                                 char **pass, t_client *client);
void mx_correct_data(t_client *client);

