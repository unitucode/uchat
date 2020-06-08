#pragma once

#include "utils.h"
#include "protocol.h"
#include "list.h"
#include "sqlite3.h"

#define MX_LISTENQ 1024
#define MX_PORT_LEN 8
#define MX_OLD_MESSAGE 2
#define MX_NEW_MESSAGE 1
#define MX_CURR_MESSAGE 0
#define MX_DB "database.db"

typedef struct s_chat t_chat;
typedef struct s_client t_client;

typedef struct s_members_room {
    char *login;
    struct s_members_room *next;
}              t_members_room;

typedef struct s_db_user {
    const char *token;
    const char *login;
    const char *password;
    unsigned int permission;
    int on_off;
}              t_db_user;

typedef struct s_db_gmp {
    long int date;
    int count;
    char *name_room;
    sqlite3 *db;
    int flag;
}              t_db_gmp;

typedef struct s_db_message {
    unsigned int id_room;
    unsigned int id_message;
    long int date;
    char *name_room;
    char *login;
    char *message;
}              t_db_message;

typedef struct s_db_room {
    long int date;
    unsigned int id;
    char *name_room;
    char *customer;
}              t_db_room;

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
t_dtp *mx_token_request(char *token);
t_dtp *mx_error_msg_request(int error_code, char *msg);
t_dtp *mx_online_users_request(int count);

//data protocol handler functions
bool mx_log_in(t_dtp *login, t_client *client);
bool mx_sign_up(t_dtp *signup_data, t_client *client);
bool mx_log_in_token(t_dtp *token, t_client *client);
bool mx_new_room(t_dtp *data, t_client *client);
bool mx_msg(t_dtp *data, t_client *client);
bool mx_get_rooms_handler(t_dtp *data, t_client *client);

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


//sqlite3 vlad struk


sqlite3 *mx_server_data_open(char *name_db);
void mx_close_database(sqlite3 *database);
void mx_free_user(t_db_user **user);
void mx_delete_room(sqlite3 *database, char *name_room);
void mx_delete_user(sqlite3 *database, char *login);

void mx_create_table_users(sqlite3 *database);
void mx_create_table_rooms(sqlite3 *database);
void mx_create_table_member(sqlite3 *database);

t_db_user *mx_get_user_by_login(sqlite3 *database, char *login);
t_db_user *mx_get_user_by_token(sqlite3 *database, char *token);
t_db_room *mx_get_room(sqlite3 *database, char *name_room);
void mx_free_room(t_db_room **room);
void mx_free_message(t_db_message **message);

    void mx_update_permission_of_user(sqlite3 *database,
                                      unsigned int permission, char *login);
void mx_update_token(sqlite3 *database, char *new_token, char *login);

void mx_create_table_room(sqlite3 *database, char *name_room);
void mx_insert_to_room(sqlite3 *database, t_db_message *room, char *name_room);

t_db_message *mx_insert_message_into_db(sqlite3 *database, char *message_str,
                                     char *login, char *name_room);
t_db_room *mx_insert_room_into_db(sqlite3 *database, char *name_room,
                               char *customer);
t_db_user *mx_insert_user_into_db(sqlite3 *database, char *login,
                               char *pass, char *token);
void mx_insert_member_into_db(sqlite3 *database,
                              char *login, char *name_room);

cJSON *mx_create_json_object(sqlite3 *database, char *user_login);
cJSON *mx_get_message_arr(sqlite3 *database, char *name_room, int count);
void mx_parse_message(cJSON *room_mss, t_dl_list *list);

char *mx_create_request_message(t_db_gmp *pr);
t_db_message *mx_get_last_message(sqlite3 *database, char *name_room);
cJSON *mx_get_messages(t_db_gmp *pr);
cJSON *mx_get_rooms(sqlite3 *database, long int date);

t_dl_list *mx_parse_json(char *rooms_json);
void mx_test_json();
void mx_json();
