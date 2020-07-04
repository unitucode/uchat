#include "server.h"

/*
 * Function: mx_create_table
 * -------------------------------
 * creates all initial tables in the database
 * 
 * db: closed database structure
 */
void mx_create_table(sqlite3 *db) {
    sqlite3_exec(db, "create table if not exists contacts("
                     "user_id       integer not null,"
                     "contact_id    integer not null,"
                     "type          integer not null);",
                 0, 0, 0);
    sqlite3_exec(db, "create table if not exists queue("
                     "user_id       integer not null,"
                     "request       text    not null,"
                     "date          text    not null);",
                 0, 0, 0);
    sqlite3_exec(db, "create table if not exists members("
                     "user_id        integer not null,"
                     "room_id        integer not null,"
                     "date           integer not null,"
                     "permission     integer not null);",
                 0, 0, 0);
    mx_create_table_users(db);
    mx_create_table_rooms(db);
    mx_create_table_messages(db);
}

/*
 * Function: mx_create_table_messages
 * -------------------------------
 * Create table messages
 * 
 * db: closed database structure
 */
void mx_create_table_messages(sqlite3 *db) {
    sqlite3_exec(db, "create table if not exists messages("
                     "user_id       integer             not null,"
                     "room_id       integer             not null,"
                     "message_id    integer primary key not null,"
                     "date          integer             not null,"
                     "message       text                        ,"
                     "type          integer             not null,"
                     "file_size     integer                     ,"
                     "file_name     text                        ,"
                     "status        integer             not null,"
                     "power         integer             not null);", 0, 0, 0);
}

/*
 * Function: mx_create_table_users
 * -------------------------------
 * create table users
 * 
 * db: closed database structure
 */
void mx_create_table_users(sqlite3 *db) {
    sqlite3_exec(db, "create table if not exists users("
                           "id             integer primary key not null,"
                           "name           text                not null,"
                           "login          text  unique        not null,"
                           "pass           text                not null,"
                           "token          text                not null,"
                           "date           integer             not null,"
                           "desc           text                );",
                 0, 0, 0);
}

/*
 * Function: mx_create_table_rooms
 * -------------------------------
 * create table rooms
 * 
 * db: closed database structure
 */
void mx_create_table_rooms(sqlite3 *db) {
    sqlite3_exec(db, "create table if not exists rooms("
                           "id                 integer primary key not null,"
                           "name               text                not null,"
                           "customer_id        integer             not null,"
                           "date               int                 not null,"
                           "desc               text,"
                           "type               int                 not null,"
                           "power              integer             not null);",
                        0, 0, 0);
}
