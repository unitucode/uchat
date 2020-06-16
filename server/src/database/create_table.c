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
                     "message       text                not null,"
                     "type          integer             not null,"
                     "format        text                not null);", 0, 0, 0);
}

void mx_create_table_queue(sqlite3 *db) {
    sqlite3_exec(db, "create table if not exists queue("
                     "user_id       integer not null,"
                     "request       text    not null,"
                     "date          text    not null);", 0, 0, 0);
}

void mx_create_table_contact(sqlite3 *db) {
    sqlite3_exec(db, "create table if not exists contacts("
                     "user_id       integer not null,"
                     "contact_id    integer not null,"
                     "type          integer not null);", 0, 0, 0);
}

void mx_create_table_users(sqlite3 *database) {
    // sqlite3_stmt *stmt;

    // sqlite3_prepare_v2(database, "select sql from sqlite_master"
    //                              " where name = 'users'",
    //                    -1, &stmt, NULL);
    // sqlite3_step(stmt);
    // check_correct_table(database, stmt);
    sqlite3_exec(database, "create table if not exists users("
                           "id             integer primary key not null"
                           "login          text  unique        not null,"
                           "password       text                not null,"
                           "token          text                not null,"
                           "date           integer             not null,"
                           "description    text                not null);", 0, 0, 0);
}

void mx_create_table_rooms(sqlite3 *database) {
    // sqlite3_stmt *stmt;

    // sqlite3_prepare_v2(database, "select sql from sqlite_master"
    //                              " where name = 'rooms'",
    //                    -1, &stmt, NULL);
    // sqlite3_step(stmt);
    // check_correct_table_rooms(database, stmt);
    sqlite3_exec(database, "create table if not exists rooms("
                           "id                 integer primary key not null,"
                           "name               text                not null,"
                           "customer           text                not null,"
                           "date               int                 not null,"
                           "desc               text);",
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
void mx_create_table_room(sqlite3 *db, unsigned long long int id) {
    sqlite3_str *str = sqlite3_str_new(db);
    sqlite3_str *str2 = sqlite3_str_new(db);
    char *request = NULL;

    sqlite3_str_appendf(str, "drop table if exists room%llu", id);
    request = sqlite3_str_finish(str);
    sqlite3_exec(db, request, 0, 0, 0);
    sqlite3_free(request);
    sqlite3_str_appendf(str2, "create table room%llu "
                              "(id_message  integer primary key not null,"
                              "login        text    not null,"
                              "date         integer not null,"
                              "message      text    not null,"
                              "type         integer not null);",id, id);
    request = sqlite3_str_finish(str2);
    sqlite3_exec(db, request, 0, 0, 0);
    sqlite3_free(request);
}

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
