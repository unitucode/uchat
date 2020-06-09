#pragma once

#include "utils.h"
#include "protocol.h"
#include "list.h"
#include "sqlite3.h"

#define MX_LISTENQ 1024
#define MX_PORT_LEN 8
#define MX_OLD_MESSAGE 2
#define MX_NEW_MESSAGE 1
#define MX_CURR_MESSAGE 0
#define MX_DB "database.db"

typedef struct s_members_room {
    char *login;
    struct s_members_room *next;
}              t_members_room;

typedef struct s_db_user {
    const char *token;
    const char *login;
    const char *password;
    unsigned int permission;
    long int date;
}              t_db_user;

typedef struct s_db_message {
    unsigned int id_room;
    unsigned int id_message;
    long int date;
    char *name_room;
    char *login;
    char *message;
}              t_db_message;

typedef struct s_db_room {
    long int date;
    unsigned int id;
    char *name_room;
    char *customer;
}              t_db_room;

sqlite3 *mx_server_data_open(char *name_db);
void mx_close_database(sqlite3 *database);
void mx_free_user(t_db_user **user);
void mx_delete_room(sqlite3 *database, char *name_room);
void mx_delete_user(sqlite3 *database, char *login);
void mx_delete_message(sqlite3 *database, char *name_room, int id_message);

void mx_create_table_users(sqlite3 *database);
void mx_create_table_rooms(sqlite3 *database);
void mx_create_table_member(sqlite3 *database);

t_db_user *mx_get_user_by_login(sqlite3 *database, char *login);
t_db_user *mx_get_user_by_token(sqlite3 *database, char *token);
t_db_room *mx_get_room(sqlite3 *database, char *name_room);
void mx_free_room(t_db_room **room);
void mx_free_message(t_db_message **message);

void mx_update_permission_of_user(sqlite3 *database,
                                  unsigned int permission, char *login);
void mx_update_token(sqlite3 *database, char *new_token, char *login);

void mx_create_table_room(sqlite3 *database, char *name_room);

void mx_insert_to_room(sqlite3 *database, t_db_message *room, char *name_room);
t_db_message *mx_insert_message_into_db(sqlite3 *database, char *message_str,
                                        char *login, char *name_room);
t_db_room *mx_insert_room_into_db(sqlite3 *database, char *name_room,
                                  char *customer);
t_db_user *mx_insert_user_into_db(sqlite3 *database, char *login,
                                  char *pass, char *token);
void mx_insert_member_into_db(sqlite3 *database,
                              char *login, char *name_room);

cJSON *mx_get_new_messages(sqlite3 *database, char *name_room,
                           long int date, int count);
cJSON *mx_get_old_messages(sqlite3 *database, char *name_room,
                           long int date, int count);
cJSON *mx_get_curr_messages(sqlite3 *database, char *name_room, int count);
char *mx_create_request_message(sqlite3 *database, char *name_room, int flag);
t_db_message *mx_get_last_message(sqlite3 *database, char *name_room);
cJSON *mx_get_rooms(sqlite3 *database, long int date);

void mx_test_json();
void mx_json();