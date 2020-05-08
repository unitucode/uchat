#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <netdb.h>
#include <pthread.h>
#include <errno.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <sys/stat.h>


#define MX_LIST_BACK 0
#define MX_LOG_FILE "info.log"
#define MX_ROOM_CONFIG "room_config.json"

typedef struct s_node {
    void *data;
    struct s_node *next;
}              t_node;

typedef struct s_list {
    size_t size;
    t_node *head;
}              t_list;

typedef struct s_sockopt {
    int socket;
    int level;
    int option_name;
    const void *option_value;
    socklen_t option_len;
}              t_sockopt;

typedef enum e_logtype {
    LOGMSG,
    LOGWAR,
    LOGERR
}            t_logtype;


typedef enum e_msg_types {
    MX_LOGIN = 48,
    MX_PASSWORD = 49,
    MX_USER_COUNT = 50,
    MX_MESSAGE = 51,
    MX_FILE = 52
}            t_msg_types;

typedef struct s_pds { // Protocol Data Short view
    char *data;
    char *len;
}              t_pds;

typedef struct s_pdl { // Protocol Data Long view
    int type;
    char *data;
    char *len;
}              t_pdl;



//wrappers
void *mx_malloc(size_t size);
int mx_socket(int domain, int type, int protocol);
int mx_setsockopt(t_sockopt *sockopt);
int mx_close(int fd);
int mx_listen(int socket, int backlog);
int mx_accept(int socket, struct sockaddr *restrict address,
              socklen_t *restrict address_len);
int mx_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg);
int mx_getaddrinfo(const char *hostname, const char *servname,
                   const struct addrinfo *hints, struct addrinfo **res);
int mx_pthread_mutex_init(pthread_mutex_t *mutex,
                          const pthread_mutexattr_t *attr);
int mx_pthread_mutex_destroy(pthread_mutex_t *mutex);
int mx_pthread_mutex_lock(pthread_mutex_t *mutex);
int mx_pthread_mutex_unlock(pthread_mutex_t *mutex);

//list
void mx_push_node(t_list *list, void *data, size_t index);
void mx_remove_node(t_list *list, size_t index);
t_node *mx_new_node(void *data);
t_list *mx_new_list();
void mx_delete_list(t_list **list);

//logs
void mx_log_id(FILE *fd);
void mx_log_time(FILE *fd);
void mx_log_errno(FILE *fd);
void mx_log_type(FILE *fd, t_logtype type);
void mx_logger(const char *file, t_logtype type, const char *fmt, ...);
void mx_elogger(const char *file, t_logtype type, const char *fmt, ...);

//Protocol
t_pds *mx_request_creation(int req_type, char *request);
t_pdl *mx_request_decode(char *request);
void mx_free_request_struct(t_pds **request);
void mx_free_decode_struct(t_pdl **decode_req);
void mx_strdel(void **tds);
char *mx_itoa(int number);

//room_config
char *mx_open_room_config();
