#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <libgen.h>
#include <string.h>
#include <netdb.h>
#include <pthread.h>
#include <errno.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
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

#define MX_LIST_BACK 0
#define MX_LOG_FILE "info.log"
#define MX_REQ_REGEX "([0-9]+[|][0-9]+[|]).+" 
#define MX_HASH_REGEX "^[A-Fa-f0-9]{64}$"
#define MX_LOGIN_REGEX "^[a-z0-9_-]{3,22}$"

#define MX_CERT_FILE "certificate.crt"
#define MX_KEY_FILE "private_key.pem"
#define MX_KEY_PASSWORD "12345678"

#define MX_BUF_SIZE 1024
#define MX_MD5_BUF_SIZE 32
#define MX_SHA256_LENGTH 64

typedef enum e_app_type {
    CLIENT,
    SERVER
}            t_app_type;

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
char *mx_strdup(char *str);
void *mx_malloc(size_t size);
void mx_free(void **ptr);
int mx_close(int fd);
FILE *mx_fopen(const char * restrict path, const char * restrict mode);
int mx_fclose(FILE *stream);

//logs
void mx_log_id(FILE *fd);
void mx_log_time(FILE *fd);
void mx_log_errno(FILE *fd);
void mx_log_type(FILE *fd, t_logtype type);
void mx_logger(const char *file, t_logtype type, const char *fmt, ...);
void mx_elogger(const char *file, t_logtype type, const char *fmt, ...);

