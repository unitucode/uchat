#pragma once

#include "utils.h"
#include "protocol.h"
#include "list.h"
#include <sqlite3.h>

#define MX_LISTENQ 1024
#define MX_PORT_LEN 8

typedef struct s_chat t_chat;
typedef struct s_client t_client;

struct s_chat {
    int listen_fd;
    t_dl_list *clients;
    socklen_t len;
    pthread_mutex_t mutex;
    bool (*request_handler[RQ_COUNT_REQUEST])(t_dtp *dtp, t_client *chat);
    sqlite3* database;
};

struct s_client {
    struct sockaddr *cliaddr;
    pthread_t tid;
    socklen_t len;
    char ip[INET6_ADDRSTRLEN];
    char port[MX_PORT_LEN];
    int socket_fd;
    t_user *user;
    t_chat *chat;
    t_node *node;
    SSL *ssl;
};

//data protocol handler functions
bool mx_log_in(t_dtp *login, t_client *client);
bool mx_sign_up(t_dtp *signup_data, t_client *client);
bool mx_log_in_token(t_dtp *token, t_client *client);

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

//Authorization
bool mx_valid_authorization_data(t_dtp *data, char **login,
                                 char **pass, int type);
void mx_correct_data(char *login, t_client *client);
