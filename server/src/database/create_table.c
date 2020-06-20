#include "server.h"

void mx_create_table_member(sqlite3 *database) {
    sqlite3_exec(database, "create table if not exists members("
                           "user_id        integer not null,"
                           "room_id        integer not null,"
                           "date           integer not null,"
                           "permission     integer not null);", 0, 0, 0);
}

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
                     "date_dead     integer             not null);", 0, 0, 0);
}

void mx_create_table_queue(sqlite3 *db) {
    sqlite3_exec(db, "create table if not exists queue("
                     "user_id       integer not null,"
                     "request       text    not null,"
                     "date          text    not null);", 0, 0, 0);
}

void mx_create_table_contacts(sqlite3 *db) {
    sqlite3_exec(db, "create table if not exists contacts("
                     "user_id       integer not null,"
                     "contact_id    integer not null,"
                     "type          integer not null);", 0, 0, 0);
}

void mx_create_table_users(sqlite3 *db) {
    // sqlite3_stmt *stmt;

    // sqlite3_prepare_v2(database, "select sql from sqlite_master"
    //                              " where name = 'users'",
    //                    -1, &stmt, NULL);
    // sqlite3_step(stmt);
    // check_correct_table(database, stmt);
    sqlite3_exec(db, "create table if not exists users("
                           "id             integer primary key not null,"
                           "name           text  unique        not null,"
                           "login          text  unique        not null,"
                           "pass           text                not null,"
                           "token          text                not null,"
                           "date           integer             not null,"
                           "desc           text                );", 0, 0, 0);
}

void mx_create_table_rooms(sqlite3 *db) {
    // sqlite3_stmt *stmt;

    // sqlite3_prepare_v2(database, "select sql from sqlite_master"
    //                              " where name = 'rooms'",
    //                    -1, &stmt, NULL);
    // sqlite3_step(stmt);
    // check_correct_table_rooms(database, stmt);
    sqlite3_exec(db, "create table if not exists rooms("
                           "id                 integer primary key not null,"
                           "name               text                not null,"
                           "customer_id        integer             not null,"
                           "date               int                 not null,"
                           "desc               text,"
                           "type               int                  not null);",
                        0, 0, 0);
}

//  to delete
// static void check_correct_table(sqlite3 *db, sqlite3_stmt *stmt) {
//     char *table = NULL;

//     if (sqlite3_column_text(stmt, 0)) {
//         table = strdup((char*)sqlite3_column_text(stmt, 0));
//         sqlite3_finalize(stmt);
//         if (strcmp(table, "CREATE TABLE users(login          text  unique   "
//                           "not null,password       text           not null,t"
//                           "oken          text           not null,permission "
//                           "    integer        not null,date           intege"
//                           "r        not null,description    text           n"
//                           "ot null)") != 0) {
//             sqlite3_exec(db, "drop table users", 0, 0, 0);
//         }
//         mx_free((void**)&table);
//     }
//     else {
//         sqlite3_finalize(stmt);
//         sqlite3_exec(db, "drop table if exists users", 0, 0, 0);
//     }
// }

// to delete
// static void check_correct_table_rooms(sqlite3 *db, sqlite3_stmt *stmt) {
//     char *table = NULL;

//     if (sqlite3_column_text(stmt, 0)) {
//         table = strdup((char *)sqlite3_column_text(stmt, 0));
//         sqlite3_finalize(stmt);
//         if (strcmp(table, "CREATE TABLE rooms(id                 integer "
//                           "primary key not null,name               text  "
//                           "              not null,customer_login     text"
//                           "                not null,date               in"
//                           "teger             not null,description        "
//                           "text                not null)") != 0) {
//             sqlite3_exec(db, "drop table rooms", 0, 0, 0);
//         }
//         mx_free((void **)&table);
//     }
//     else {
//         sqlite3_finalize(stmt);
//         sqlite3_exec(db, "drop table if exists rooms", 0, 0, 0);
//     }
// }

// to delete
