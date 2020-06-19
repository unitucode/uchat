#pragma once

#include "utils.h"
#include "sqlite3.h"
#include <glib.h>
#include <sys/time.h>

#define MX_DB "database.db"

typedef struct s_member t_member;
typedef struct s_db_user t_db_user;
typedef struct s_db_message t_db_message;
typedef struct s_db_room t_db_room;

typedef enum s_type_db {
    CURR_MESSAGE = 0,
    NEW_MESSAGE,
    OLD_MESSAGE,
    CUSTOMER,
    ADMIN,
    MODERATOR,
    SIMPLE,
    STATUS_MSG_EDIT,
    STATUS_MSG_START,
    TEXT_MSG,
    FILE_MSG,
    FILE_TEXT_MSG,
    PRIVAT_CHAT,
    GLOBAL_CHAT,
    TWO_CHAT
}            t_type_db;

struct s_member{
    guint64 user_id;
    guint64 room_id;
    guint64 date;
    gint8   prm; // permission
};

struct s_db_user {
    guint64 user_id;
    guint64 date;
    gchar *pass;
    gchar *token;
    gchar *name;
    gchar *login;
    gchar *desc;
};

struct s_db_message {
    guint64 user_id;
    guint64 room_id;
    guint64 message_id;
    guint64 date;
    gint8 status;
    gint8 type;
    guint64 size;
    gchar *message;
    gchar *name_file;
};

struct s_db_room {
    guint64 date;
    guint64 room_id;
    gint8 type;
    gchar *desc;
    gchar *room_name;
    gchar *customer;
};

//create table
void mx_create_table_users(sqlite3 *db);
void mx_create_table_rooms(sqlite3 *db);
void mx_create_table_member(sqlite3 *db);
void mx_create_table_queue(sqlite3 *db);
void mx_create_table_messages(sqlite3 *db);
void mx_create_table_contacts(sqlite3 *db);

// function
guint64 mx_get_time(void);
sqlite3 *mx_open_db(gchar *name_db);
void mx_close_database(sqlite3 *db);
gchar *mx_create_request_message_by_id(sqlite3 *db, guint64 room_id,
                                       gint8 type);

//count
guint64 mx_get_count_users(sqlite3 *db);
guint64 mx_get_count_rooms(sqlite3 *db);
guint64 mx_get_count_messages(sqlite3 *db, guint64 id);

// error
gboolean mx_error_sqlite(gint32 rv, gchar *error, gchar *where_error);

// queue
void mx_db_push_queue_by_id(sqlite3 *db, guint64 user_id,
                            gchar *request);
void mx_db_pop_queue_by_id(sqlite3 *db, guint64 user_id);
gchar *mx_get_queue(sqlite3 *db, guint64 user_id);
void mx_clean_queue(sqlite3 *db, guint64 user_id);

// get
t_db_user *mx_get_user_by_login(sqlite3 *db, gchar *login);
t_db_user *mx_get_user_by_id(sqlite3 *db, guint64 user_id);
t_db_user *mx_get_user_by_token(sqlite3 *db, gchar *token);
t_db_room *mx_get_room_by_id(sqlite3 *db, guint64 id);
cJSON *mx_get_users(sqlite3 *db, guint64 date);
t_db_user *mx_get_user_by_id(sqlite3 *db, guint64 user_id);
cJSON *mx_get_rooms(sqlite3 * db, guint64 date, guint64 user_id);
cJSON *mx_get_new_messages_by_id(sqlite3 *db, guint64 room_id, guint64 date,
                                 gint64 count);
cJSON *mx_get_old_messages_by_id(sqlite3 *db, guint64 room_id, guint64 date,
                                 gint64 count);
cJSON *mx_get_curr_messages_by_id(sqlite3 *db, guint64 room_id, gint64 count);

// edit
void mx_edit_user_name_by_id(sqlite3 *db, guint64 id, gchar *new_name);
void mx_edit_room_name_by_id(sqlite3 *db, guint64 id, gchar *new_name);
void mx_edit_message_by_id(sqlite3 *db, guint64 id, gchar *new);
void mx_update_token(sqlite3 *db, guint64 user_id, gchar *new);
void mx_update_desc_user(sqlite3 *db, guint64 user_id, gchar *new);
void mx_update_desc_room_by_id(sqlite3 *db, guint64 room_id, gchar *new);
void mx_update_permission_of_user(sqlite3 *db, guint64 user_id, guint64 room_id,
                                 gint8 new);

// delete
void mx_delete_message_by_id(sqlite3 *db, guint64 id);
void mx_delete_user_by_id(sqlite3 *db, guint64 id);
void mx_delete_room_by_id(sqlite3 *db, guint64 room_id);

// insert
void mx_insert_room_into_db(sqlite3 *db, t_db_room *room);
void mx_insert_member_into_db(sqlite3 *db, guint64 room_id, guint64 user_id,
                              gint8 permission);
void mx_insert_user_into_db(sqlite3 *db, t_db_user *user);
void mx_insert_message(sqlite3 *db, t_db_message *message);

// free struct 
void mx_free_room(t_db_room **room);
void mx_free_message(t_db_message **message);
void mx_free_user(t_db_user **user);
