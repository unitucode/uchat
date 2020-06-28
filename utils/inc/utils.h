#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <stdbool.h>
#include <stdarg.h>
#include <fcntl.h>
#include <gmodule.h>
#include "sqlite3.h"
#include "cJSON.h"

#define MX_IN_ITOA(m) #m
#define MX_ITOA(m) MX_IN_ITOA(m)

#define MX_LOG_FILE "info.log"
#define MX_HASH_REGEX "^[A-Fa-f0-9]{64}$"
#define MX_LOGIN_REGEX "^[a-z0-9_-]{3,22}$"


#define MX_BUF_SIZE 1024
#define MX_MD5_BUF_SIZE 32
#define MX_SHA256_LENGTH 64

/* APPLICATION_TYPE
 * ----------
 * All types of application
 */
typedef enum e_app_type {
    CLIENT,
    SERVER
}            t_app_type;

/* LOG_TYPE
 * ----------
 * All types of logger
 */
typedef enum e_logtype {
    LOGMSG,
    LOGWAR,
    LOGERR
}            t_logtype;

//Utils
gboolean mx_match_search(gchar *str, gchar *regex);
gboolean mx_match_nsearch(gchar *str, gchar *regex, gssize size);
void mx_randomize_str(char *str, size_t count);
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
