#pragma once

#include <gio/gio.h>
#include "utils.h"
#include "protocol.h"
#include "sqlite3.h"
#include "database.h"

/*
 * Settings of server
 */
#define MX_REQUEST_PER_SECOND 20
#define MX_DELAY (1000000 / MX_REQUEST_PER_SECOND)
#define MX_MAX_ROOMS 20
#define MX_MAX_MSGS 500

/* Client
 * ----------
 * conn: connection between client and server
 * out: GDataOutputStream object
 * in: GDataOutputStream object
 * in_s: GInputStream object
 * msg: last request from client
 * user: information about this user in database
 * info: information about all chat
 */
typedef struct s_client t_client;

/* Information
 * ----------
 * users: hash table that contains all connected user
 * database: sqlite3 database connection
 * request_handler: array of handler functions
 */
typedef struct s_info t_info;

/* Send helper
 * ----------
 * table: hash table that contains all members of room
 * data: request that need to send
 */
typedef struct s_send_helper t_send_helper;

/* File helper
 * ----------
 * table: hash table that contains all members of room
 * data: request that need to send
 */
typedef struct s_file_helper t_file_helper;

struct s_file_helper {
    t_client *client;
    guint64 size;
    guint64 room_id;
    gchar *name;
};

struct s_info {
    GHashTable *users;
    sqlite3* database;
    gboolean (*request_handler[RQ_COUNT_REQUEST])(t_dtp *dtp, t_client *chat);
};

struct s_client {
    GSocketConnection *conn;
    GDataOutputStream *out;
    GDataInputStream *in;
    GInputStream *in_s;
    char *msg;
    t_db_user *user;
    t_info *info;
    gboolean upload_file;
    gboolean is_file;
};

struct s_send_helper {
    GHashTable *table;
    t_dtp *data;
};

gssize mx_send(GDataOutputStream *out, t_dtp *dtp);
t_info *mx_init_info(void);
void mx_deinit_info(t_info **info);
void mx_deinit_client(t_client **client);
void mx_init_receiver(t_info *chat);

void mx_get_client_info(t_client *client);
void mx_connect_client(t_client *client);
void mx_disconnect_client(t_client *client);
void mx_delete_client(void **client);
void *mx_receiver(void *arg);
void mx_send_to_all(t_dtp *data, t_client *client, guint64 room_id);
void mx_daemon(void);
//Authorization
gboolean mx_valid_authorization_data(t_dtp *data, char **login,
                                 char **pass, t_client *client);
void mx_correct_data(t_client *client);
gdouble mx_get_used_power(guint64 chars);
