#include "utils.h"

static void check_correct_table(sqlite3 *db, sqlite3_stmt *stmt) {
    char *table = NULL;

    if (sqlite3_column_text(stmt, 0)) {
        table = strdup((char*)sqlite3_column_text(stmt, 0));
        sqlite3_finalize(stmt);
        if (strcmp(table, "CREATE TABLE users(login          "
                          "text  unique   not null,password  "
                          "     text           not null,token"
                          "          text           not null,"
                          "permission     integer        not "
                          "null,date           integer       "
                          " not null,description    text)") != 0) {
            sqlite3_exec(db, "drop table users", 0, 0, 0);
        }
        mx_free((void**)&table);
    }
    else {
        sqlite3_finalize(stmt);
        sqlite3_exec(db, "drop table users", 0, 0, 0);
    }
}

void mx_create_table_users(sqlite3 *database) {
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(database, "select sql from sqlite_master"
                                 " where name = 'users'",
                       -1, &stmt, NULL);
    sqlite3_step(stmt);
    check_correct_table(database, stmt);
    sqlite3_exec(database, "create table if not exists users("
                           "login          text  unique   not null,"
                           "password       text           not null,"
                           "token          text           not null,"
                           "permission     integer        not null,"
                           "date           integer        not null,"
                           "description    text);", 0, 0, 0);
}

void mx_create_table_member(sqlite3 *database) {
    sqlite3_exec(database, "CREATE TABLE IF NOT EXISTS MEMBER("
                           "NAME_ROOM        TEXT NOT NULL,"
                           "LOGIN            TEXT    NOT NULL);",
                 0, 0, 0);
}

void mx_create_table_room(sqlite3 *database, int id) {
    sqlite3_str *str = sqlite3_str_new(database);
    char *sql = NULL;

    sqlite3_str_appendall(str, "CREATE TABLE IF NOT EXISTS ");
    sqlite3_str_appendf(str, "room%d", id);
    sqlite3_str_appendall(str,
                        " (ID_MESSAGE INTEGER PRIMARY KEY NOT NULL,"
                          "LOGIN        TEXT NOT NULL,"
                          "DATE         INTEGER NOT NULL,"
                          "MESSAGE      TEXT NOT NULL);");
    sql = sqlite3_str_finish(str);
    sqlite3_exec(database, sql, 0, 0, 0);
    sqlite3_free(sql);
}

void mx_create_table_rooms(sqlite3 *database) {
    sqlite3_exec(database, "CREATE TABLE IF NOT EXISTS ROOMS("
                       "ID                 INTEGER PRIMARY KEY NOT NULL,"
                       "NAME          TEXT                NOT NULL, "
                       "CUSTOMER_LOGIN     TEXT                NOT NULL,"
                       "DATE               INTEGER             NOT NULL,"
                       "DESCRIPTION        TEXT                NOT NULL);",
                        0, 0, 0);
}
