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
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <openssl/rand.h>
#include <regex.h>
#include <time.h>
#include "sqlite3.h"
#include "cJSON.h"
#include "list.h"

#define MX_IN_ITOA(m) #m
#define MX_ITOA(m) MX_IN_ITOA(m)
#define MX_DB_USER "users.db"

#define MX_LIST_BACK 0
#define MX_LOG_FILE "info.log"
#define MX_CONFIG "config.json"
#define MX_DEFAULT_CONFIG "{\n\n}\n"
#define MX_REQ_REGEX "([0-9]+[|][0-9]+[|]).+" 
#define MX_HASH_REGEX "^[a-f0-9]{32}$"
#define MX_LOGIN_REGEX "^[a-z0-9_-]{3,22}$"

#define MX_CERT_FILE "certificate.crt"
#define MX_KEY_FILE "private_key.pem"
#define MX_KEY_PASSWORD "12345678"

#define MX_BUF_SIZE 1024
#define MX_MD5_BUF_SIZE 32

typedef enum e_app_type {
    CLIENT,
    SERVER
}            t_app_type;

typedef struct s_id_room {
    char *text;
    int id_room;
    struct s_id_room *next;
}              t_id_room;

typedef struct s_members_room {
    char *login;
    struct s_members_room *next;
}              t_members_room;

typedef struct s_user {
    const char *token;
    const char *login;
    const char *password;
    unsigned int permission;
    int on_off;
}              t_user;

typedef struct s_message {
    unsigned int id_room;
    unsigned int id_message;
    long int date;
    char *login;
    char *message;
    // cJSON *message;
    struct s_messages *next;
}              t_message;

typedef struct s_room {
    unsigned int id;
    char *name;
    char *customer;
    t_message *data;
}              t_room;

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

//Utils
bool mx_match_search(char *str, char *regex);
bool mx_match_nsearch(char *str, char *regex, size_t size);
void mx_randomize_str(char *str, size_t count);
void *mx_memdup(const void *mem, size_t size);
long long mx_get_current_time(void);


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

//logs
void mx_log_id(FILE *fd);
void mx_log_time(FILE *fd);
void mx_log_errno(FILE *fd);
void mx_log_type(FILE *fd, t_logtype type);
void mx_logger(const char *file, t_logtype type, const char *fmt, ...);
void mx_elogger(const char *file, t_logtype type, const char *fmt, ...);

//sqlite3
sqlite3 *mx_server_data_open(char *name_db);
void mx_close_database(sqlite3 *database);
void mx_free_user(t_user **user);
void mx_delete_room(sqlite3 *database, int id_room);
void mx_delete_user(sqlite3 *database, char *login);

void mx_create_table_users(sqlite3 *database);
void mx_create_table_rooms(sqlite3 *database);
void mx_create_table_member(sqlite3 *database);

t_user *mx_get_user_by_login(sqlite3 *database, char *login);
t_user *mx_get_user_by_token(sqlite3 *database, char *token);
t_room *mx_get_room(sqlite3 *database,char *name_room);

void mx_update_permission_of_user(sqlite3 *database, 
                                  unsigned int permission, char *login);
void mx_update_token(sqlite3 *database, char *new_token, char *login);

// t_user *mx_insert_user(sqlite3 *database, char *login, char *password, char *token);
// void mx_insert_message(sqlite3 *database, char *login, long long date, char *json);
// void mx_insert_memeber(sqlite3 *database, int id_room, char *login);
// t_room *mx_insert_room(sqlite3 *database, char *customer, char *name_room);

void mx_create_table_room(sqlite3 *database, char *name_room);
void mx_insert_to_room(sqlite3 *database, t_message *room, char *name_room);

t_message *mx_insert_message_into_db(sqlite3 *database, char *message_str,
                                     char *login, char *name_room);
t_room *mx_insert_room_into_db(sqlite3 *database, char *name_room,
                               char *customer);
t_user *mx_insert_user_into_db(sqlite3 *database, char *login,
                               char *pass, char *token);
void mx_insert_into_member(sqlite3 *database,
                           char *login, char *name_room);


cJSON *mx_create_json_object(sqlite3 *database, char *user_login);
cJSON *mx_create_json_message(sqlite3 * database, char *name_room,
                              long long date);
cJSON *mx_get_message_arr(char *name_room, sqlite3 *database);
cJSON *mx_get_object_message(sqlite3_stmt * stmt);
cJSON *mx_get_last_message(sqlite3 * database,
                               char *name_room, long int date);

void mx_parse_message(cJSON * room_mss, t_dl_list * list);

t_dl_list *mx_parse_json(char *rooms_json);
void mx_test_json();
void mx_json();
// void mx_test_room();
// void mx_test_member();
// void mx_test_users();
// void mx_test_message();
