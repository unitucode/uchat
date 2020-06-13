#pragma once

#include "utils.h"
#include "sqlite3.h"

#define MX_OLD_MESSAGE 2
#define MX_NEW_MESSAGE 1
#define MX_CURR_MESSAGE 0
#define MX_DB "database.db"

typedef struct s_members_room {
    char *login;
    char *name_room;
    struct s_members_room *next;
}              t_members_room;

typedef struct s_db_user {
    unsigned int permission;
    long int date;
    char *password;
    char *token;
    char *login;
    char *description;
}              t_db_user;

typedef struct s_db_message {
    unsigned int id;
    unsigned int room_id;
    long int date;
    char *name_room;
    char *login;
    char *message;
}              t_db_message;

typedef struct s_db_room {
    long int date;
    unsigned int id;
    char *description;
    char *room_name;
    char *customer;
}              t_db_room;

sqlite3 *mx_server_data_open(char *name_db);
void mx_close_database(sqlite3 *database);
void mx_free_user(t_db_user **user);
void mx_delete_room(sqlite3 *database, char *name_room);
void mx_delete_user(sqlite3 *database, char *login);
void mx_delete_message(sqlite3 *database, unsigned long long int id,
                       unsigned long long int id_message);
void mx_delete_room_by_id(sqlite3 *db, unsigned long long int id);

void mx_create_table_users(sqlite3 *database);
void mx_create_table_rooms(sqlite3 *database);
void mx_create_table_member(sqlite3 *database);
void mx_create_table_room(sqlite3 *database, unsigned long long int id);
void mx_create_table_queue(sqlite3 *db, char *login);

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

t_db_message *mx_insert_message_into_db_by_id(sqlite3 *db, char *message_str,
                                        char *login,
                                        unsigned long long int id);
void mx_insert_to_room(sqlite3 * database, t_db_message * room, char *name_room);
t_db_message *mx_insert_message_into_db(sqlite3 * database, char *message_str,
                                            char *login, char *name_room);
t_db_room *mx_insert_room_into_db(sqlite3 * database, char *name_room,
                                      char *customer);
t_db_user *mx_insert_user_into_db(sqlite3 * database, char *login,
                                      char *pass, char *token);
void mx_insert_member_into_db(sqlite3 * database,
                                  char *login, char *name_room);

cJSON *mx_get_new_messages(sqlite3 * database, char *name_room,
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

unsigned long long int mx_get_count_users(sqlite3 *db);
unsigned long long int mx_get_count_rooms(sqlite3 *db);
unsigned long long int mx_get_count_messages(sqlite3 *db,
                                             unsigned long long int id);


// error
int mx_error_sqlite(int rv, char *error, char *where_error);
bool mx_is_exists_room_by_id(sqlite3 *db, unsigned long long int id);
