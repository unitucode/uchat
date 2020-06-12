#pragma once

#include "utils.h"
#include "protocol.h"
#include "list.h"
#include "sqlite3.h"
#include "database.h"

//settings
#define MX_LISTENQ 1024
#define MX_PORT_LEN 8
#define MX_REQUEST_PER_SECOND 20
#define MX_DELAY (1000000 / MX_REQUEST_PER_SECOND)
#define MX_MAX_ROOMS 20
#define MX_MAX_MSGS 500

typedef struct s_chat t_chat;
typedef struct s_client t_client;
// typedef struct s_members_room t_members_room;
// typedef struct s_db_user t_db_user;
// typedef struct s_db_message t_db_message;
// typedef struct s_db_room t_db_room;

struct s_chat {
    int listen_fd;
    t_dl_list *clients;
    socklen_t len;
    pthread_mutex_t mutex;
    bool (*request_handler[RQ_COUNT_REQUEST])(t_dtp *dtp, t_client *client);
    sqlite3* database;
    int online_users;
};

struct s_client {
    struct sockaddr *cliaddr;
    pthread_t tid;
    socklen_t len;
    char ip[INET6_ADDRSTRLEN];
    char port[MX_PORT_LEN];
    int socket_fd;
    t_db_user *user;
    t_chat *chat;
    t_node *node;
    SSL *ssl;
};

//api
t_dtp *mx_token_request(char *token, char *login);
t_dtp *mx_error_msg_request(int error_code, char *msg);
t_dtp *mx_online_users_request(int count);
t_dtp *mx_log_out_request(char *token);
t_dtp *mx_upd_room_desc_request(int room_id, char *room_name);
t_dtp *mx_upd_room_name_request(int room_id, char *room_name);
t_dtp *mx_upd_user_desc_request(char *name, char *desc);

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

int mx_tcp_listen(const char *serv, socklen_t *addr_len);
void mx_get_client_info(t_client *client);
t_client *mx_new_client(socklen_t len);
t_chat *mx_init_chat(int argc, char **argv);
void mx_deinit_chat(t_chat **chat);
void mx_connect_client(t_client *client);
void mx_disconnect_client(t_client *client);
void mx_delete_client(void **client);
void mx_init_receiver(t_chat *chat);
void *mx_receiver(void *arg);
void mx_send_to_all(t_dtp *data, t_client *client);
void mx_update_online(int count, t_client *client);

//Authorization
bool mx_valid_authorization_data(t_dtp *data, char **login,
                                 char **pass, t_client *client);
void mx_correct_data(char *login, t_client *client);

