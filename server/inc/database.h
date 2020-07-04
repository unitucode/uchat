#pragma once

#include "utils.h"
#include "sqlite3.h"
#include "protocol.h"

#define MX_DB "database.db"

typedef struct s_member t_member;
typedef struct s_db_user t_db_user;
typedef struct s_db_message t_db_message;
typedef struct s_db_room t_db_room;

typedef enum e_type_db {
    DB_NEW_MESSAGE = 0,
    DB_OLD_MESSAGE,
    DB_SECOND,
    DB_MILISECOND,
    DB_MICROSECOND
}            t_type_db;

struct s_member{
    guint64 user_id;
    guint64 room_id;
    guint64 date;
    gint8   prm;
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
    guint64 file_size;
    guint64 power;
    gchar *message;
    gchar *file_name;
};

struct s_db_room {
    guint64 date;
    guint64 room_id;
    guint64 customer_id;
    gint8 type;
    guint64 power;
    gchar *desc;
    gchar *room_name;
};

cJSON *mx_json_is_valid(cJSON *data, gchar *str,
                        cJSON_bool (*check_valid)(const cJSON *const));
t_db_user *mx_parse_json_user(cJSON *user_j);
t_db_room *mx_parse_json_room(cJSON *room_j);
t_db_message *mx_parse_message(cJSON *message_j);

//create table 
void mx_create_table(sqlite3 *db);
void mx_create_table_users(sqlite3 *db);
void mx_create_table_rooms(sqlite3 *db);
void mx_create_table_messages(sqlite3 *db);

// function 
guint64 mx_get_time(gint8 type);
sqlite3 *mx_open_db(gchar *name_db);
void mx_close_db(sqlite3 *db);
gchar *mx_create_request_message_by_id(sqlite3 *db, guint64 room_id,
                                       gint8 type);

//count
guint64 mx_get_count_users(sqlite3 *db);
guint64 mx_get_count_rooms(sqlite3 *db);
guint64 mx_get_count_messages(sqlite3 *db, guint64 id);

// error
gboolean mx_error_sqlite(gint32 rv, char *error);

// queue
void mx_db_push_queue_by_id(sqlite3 *db, guint64 user_id,
                            gchar *request);
void mx_db_pop_queue_by_id(sqlite3 *db, guint64 user_id);
gchar *mx_get_queue(sqlite3 *db, guint64 user_id);
void mx_clean_queue(sqlite3 *db, guint64 user_id);

// get
cJSON *mx_get_object_room(sqlite3_stmt *stmt);
cJSON *mx_get_object_user(sqlite3_stmt *stmt);
t_db_user *mx_get_user_by_login(sqlite3 *db, gchar *login);
t_db_user *mx_get_user_by_token(sqlite3 *db, gchar *token);
t_db_user *mx_get_user_by_id(sqlite3 *db, guint64 user_id);
t_db_room *mx_get_room_by_id(sqlite3 *db, guint64 id);
cJSON *mx_get_users(sqlite3 *db, guint64 date);
cJSON *mx_get_rooms(sqlite3 * db, guint64 date, guint64 user_id);
cJSON *mx_get_new_messages_by_id(sqlite3 *db, guint64 room_id, guint64 date,
                                 gint64 count);
cJSON *mx_get_old_messages_by_id(sqlite3 *db, guint64 room_id, guint64 date,
                                 gint64 count);

// edit
void mx_edit_user_name_by_id(sqlite3 *db, guint64 id, gchar *new_name);
void mx_edit_room_name_by_id(sqlite3 *db, guint64 id, gchar *new_name);
void mx_edit_message_by_id(sqlite3 *db, guint64 id, gchar *new);
void mx_edit_token(sqlite3 *db, guint64 user_id, gchar *new);
void mx_edit_desc_user(sqlite3 *db, guint64 user_id, gchar *new);
void mx_edit_desc_room_by_id(sqlite3 *db, guint64 room_id, gchar *new);
void mx_edit_permission_of_user(sqlite3 *db, guint64 user_id, guint64 room_id,
                                 gint8 new);

// delete
void mx_delete_message_by_id(sqlite3 *db, guint64 id);
void mx_delete_user_by_id(sqlite3 *db, guint64 id);
void mx_delete_room_by_id(sqlite3 *db, guint64 room_id);
void mx_delete_all_messages(sqlite3 *db, guint64 room_id);

// insert yes
void mx_insert_room_into_db(sqlite3 *db, t_db_room *room);
void mx_insert_user_into_db(sqlite3 *db, t_db_user *user);
void mx_insert_message(sqlite3 *db, t_db_message *message);

// free struct
void mx_free_room(t_db_room **room);
void mx_free_message(t_db_message **message);
void mx_free_user(t_db_user **user);


//contact
void mx_insert_contact(sqlite3 *db, guint64 user_id, guint64 contact_id,
                       gint8 type);
void mx_delete_contact(sqlite3 *db, guint64 user_id, guint64 contact_id);
cJSON *mx_get_contacts(sqlite3 *db, guint64 user_id, gint8 type);

// user
gboolean mx_is_member(sqlite3 *db, guint64 user_id, guint64 room_id);

// search
gboolean mx_check_user_by_login(sqlite3 *db, gchar *login);
cJSON *mx_search_room(sqlite3 *db, gchar *str_search, guint64 user_id);
cJSON *mx_search_user(sqlite3 *db, gchar *str_search);
cJSON *mx_search_message(sqlite3 *db, gchar *str_search, guint64 room_id);

//members
cJSON *mx_get_json_members(sqlite3 *db, guint64 room_id);
GList *mx_get_login_members(sqlite3 *db, guint64 room_id);
void mx_insert_member_into_db(sqlite3 *db, guint64 room_id, guint64 user_id,
                              gint8 permission);
void mx_destroy_data(gpointer data);
void mx_edit_type_member(sqlite3 *db, guint64 room_id, guint64 user_id,
                         gint8 new_type);
gint8 mx_get_type_member(sqlite3 *db, guint64 user_id, guint64 room_id);

// message
gboolean mx_is_owner_msg(sqlite3 *db, guint64 user_id, guint64 msg_id);
cJSON *mx_get_object_message(sqlite3_stmt *stmt);
gchar *mx_get_text_message_by_id(sqlite3 *db, guint64 message_id);

// power
guint64 mx_get_power_of_message(sqlite3 *db, guint64 message_id);
guint64 mx_get_power_of_room(sqlite3 *db, guint64 room_id);
void mx_db_update_room_power(sqlite3 *db, guint64 power, guint64 room_id);
