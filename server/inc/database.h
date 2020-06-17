#pragma once

#include "utils.h"
#include "sqlite3.h"
#include <glib.h>
#include <sys/time.h>

#define MX_CUSTOMER 1
#define MX_ADMIN 2
#define MX_MODERATOR 3
#define MX_USER 4

#define MX_STATUS_MSG_EDIT 1
#define MX_STATUS_MSG_START 2

#define MX_TEXT_MSG 1
#define MX_FILE_MSG 2

#define MX_OLD_MESSAGE 2
#define MX_NEW_MESSAGE 1
#define MX_CURR_MESSAGE 0
#define MX_DB "database.db"

typedef struct s_member t_member;
typedef struct s_db_user t_db_user;
typedef struct s_db_message t_db_message;
typedef struct s_db_room t_db_room;

struct s_member{
    guint64 user_id;
    guint64 room_id;
    guint64 date;
    gint8   prm; // permission
};

struct s_db_user {
    guint64 date;
    gchar *pass;
    gchar *token;
    gchar *name;
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
    gchar *desc;
    gchar *room_name;
    gchar *customer;
};

sqlite3 *mx_open_db(char *name_db);
void mx_close_database(sqlite3 *database);
void mx_free_user(t_db_user **user);
void mx_delete_room(sqlite3 *database, char *name_room);
void mx_delete_user(sqlite3 *database, char *login);
void mx_delete_message(sqlite3 *database, unsigned long long int id,
                       unsigned long long int id_message);
void mx_delete_room_by_id(sqlite3 *db, unsigned long long int id);
void mx_db_pop_queue(sqlite3 *db, char *login);

void mx_create_table_users(sqlite3 *database);
void mx_create_table_rooms(sqlite3 *database);
void mx_create_table_member(sqlite3 *database);
void mx_create_table_room(sqlite3 *database, unsigned long long int id);
void mx_create_table_queue(sqlite3 *db);

char *mx_get_queue(sqlite3 *db, char *login);
t_db_user *mx_get_user_by_login(sqlite3 *database, char *login);
t_db_user *mx_get_user_by_token(sqlite3 *database, char *token);
t_db_room *mx_get_room(sqlite3 *database, char *name);
t_db_room *mx_get_room_by_id(sqlite3 *database, unsigned long long int id);
unsigned long long int mx_get_roomid_by_name(sqlite3 *db, char *name);

void mx_free_room(t_db_room **room);
void mx_free_message(t_db_message **message);


void mx_update_permission_of_user(sqlite3 *database, char *login, 
                                  unsigned int new);
void mx_update_token(sqlite3 *database, char *login, char *new);
void mx_update_description_user(sqlite3 *database, char *login, char *new);
void mx_update_description_room(sqlite3 *database, char *name, char *new);
void mx_update_description_room_by_id(sqlite3 *db, unsigned long long int id,
                                      char *new);
void update(sqlite3_stmt *stmt, char *new, char *name, char *error);
void mx_edit_name_room(sqlite3 *database, unsigned long long int id, char *new);
void mx_edit_name_user(sqlite3 *database, char *login, char *new);
void mx_edit_message_by_id(sqlite3 *db, unsigned long long id, char *new);

t_db_message *mx_insert_message_into_db_by_id(sqlite3 *db, char *message_str,
                                                  char *login,
                                                  unsigned long long int id);
void mx_insert_to_room(sqlite3 *database, t_db_message *room, char *name_room);
t_db_message *mx_insert_message_into_db(sqlite3 * database, char *message_str,
                                            char *login, char *name_room);
t_db_room *mx_insert_room_into_db(sqlite3 * database, char *name_room,
                                      char *customer);
t_db_user *mx_insert_user_into_db(sqlite3 * database, char *login,
                                      char *pass, char *token);
void mx_db_push_queue(sqlite3 *db, char *login, char *request);

cJSON *mx_get_new_messages(sqlite3 *database, char *name_room,
                               long int date, int count);
cJSON *mx_get_old_messages(sqlite3 * database, char *name_room,
                               long int date, int count);
cJSON *mx_get_curr_messages(sqlite3 * database, char *name_room, int count);
char *mx_create_request_message(sqlite3 * database, char *name_room, int flag);
char *mx_create_request_message_by_id(sqlite3 * database,
                                          unsigned long long int id, int flag);
cJSON *mx_get_curr_messages_by_id(sqlite3 *db, unsigned long long int id, int count);
cJSON *mx_get_old_messages_by_id(sqlite3 *db, unsigned long long int id, 
                                 long int date, int count);
cJSON *mx_get_new_messages_by_id(sqlite3 *db, unsigned long long int id,
                                 long int date, int count);

t_db_message *mx_get_last_message(sqlite3 *database, unsigned long long int id,
                                  char *login);
cJSON *mx_get_rooms(sqlite3 * database, long int date);

void mx_test_json();
void mx_json();

//count 

guint64 mx_get_count_users(sqlite3 *db);
guint64 mx_get_count_rooms(sqlite3 *db);
guint64 mx_get_count_messages(sqlite3 *db, guint64 id);


// error
int mx_error_sqlite(int rv, char *error, char *where_error);
bool mx_is_exists_room_by_id(sqlite3 *db, unsigned long long int id);


// new function
void mx_db_push_queue_by_id(sqlite3 *db, guint64 user_id,
                            char *request);
void mx_delete_user_by_id(sqlite3 *db, guint64 id);
void mx_delete_room_by_id(sqlite3 *db, guint64 id);
void mx_delete_message_by_id(sqlite3 *db, guint64 id);
void mx_edit_user_name_by_id(sqlite3 *db, guint64 id, gchar *new_name);
void mx_edit_room_name_by_id(sqlite3 *db, guint64 id, gchar *new_name);
guint64 mx_get_time();
void mx_insert_member_into_db(sqlite3 *db, guint64 room_id, guint64 user_id,
                              gint8 permission);
void mx_insert_message(sqlite3 *db, t_db_message *message);

