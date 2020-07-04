#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <gmodule.h>
#include "sqlite3.h"
#include "cJSON.h"

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
gint mx_close(gint fd);
FILE *mx_fopen(const char * restrict path, const char * restrict mode);
gint mx_fclose(FILE *stream);

//logs
void mx_logger(gchar *file_name, GLogLevelFlags flags, gchar *error);
