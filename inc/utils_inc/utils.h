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
#include "json.h"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/md5.h>


#define MX_LIST_BACK 0
#define MX_LOG_FILE "info.log"
#define MX_CONFIG "config.json"
#define MX_DEFAULT_CONFIG "{\n\n}\n"

#define MX_CERT_FILE "certificate.crt"
#define MX_KEY_FILE "private_key.pem"
#define MX_KEY_PASSWORD "12345678"

#define MX_BUF_SIZE 1024
#define MX_MD5_BUF_SIZE 32

typedef enum e_app_type {
    CLIENT,
    SERVER
}            t_app_type;

typedef struct s_ssl_con {
    SSL_CTX *ctx;
    SSL *ssl;
    char *cert_file;
    char *key_file;
    char *password;
}              t_ssl_con;

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

typedef enum e_request_types {
    MX_LOGIN,
    MX_PASSWORD,
    MX_USER_COUNT,
    MX_MESSAGE,
    MX_FILE,
    MX_SIZE_MSG
}            t_request_types;

typedef struct s_pds { // Protocol Data Short view
    char *data;
    char *len;
}              t_pds;

typedef struct s_pdl { // Protocol Data Long view
    int room;
    int type;
    char *data;
    size_t len;
}              t_pdl;



//SSL
t_ssl_con *mx_init_ssl(t_app_type type);
t_pdl *mx_recv(SSL *ssl);
int mx_send(SSL *ssl, t_pds *data);
void mx_md5(char *buf, const unsigned char *str, size_t len);

//wrappers
void *mx_malloc(size_t size);
void mx_free(void **ptr);
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
FILE *mx_fopen(const char * restrict path, const char * restrict mode);
int mx_fclose(FILE *stream);

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
t_pds *mx_request_creation(int room, int req_type, char *req_body);
t_pdl *mx_request_decode(char *request);
void mx_free_request_struct(t_pds **request);
void mx_free_decode_struct(t_pdl **decode_req);
char *mx_itoa(int number);

//room_config
json_value *mx_open_config();
char *mx_get_config_val(char *key);
