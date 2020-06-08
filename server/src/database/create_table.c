#include "utils.h"

void mx_create_table_users(sqlite3 *database) {
    sqlite3_exec(database,  "CREATE TABLE USERS("
                        "LOGIN          TEXT  UNIQUE   NOT NULL,"
                        "PASSWORD       TEXT           NOT NULL,"
                        "TOKEN          TEXT           NOT NULL,"
                        "PERMISSION     INTEGER        NOT NULL,"
                        "ON_OFF         INTEGER        NOT NULL);",
                         0, 0, 0)   ;
}

void mx_create_table_member(sqlite3 *database) {
    sqlite3_exec(database, "CREATE TABLE MEMBER("
                        "NAME_ROOM        TEXT NOT NULL,"
                        "LOGIN            TEXT    NOT NULL);",
                         0, 0, 0);
}

void mx_create_table_room(sqlite3 *database, char *name_room) {
    sqlite3_str *str = sqlite3_str_new(database);
    char *sql = NULL;

    sqlite3_str_appendall(str, "CREATE TABLE '");
    sqlite3_str_appendall(str, name_room);
    sqlite3_str_appendall(str, 
                          "'(ID_MESSAGE  INTEGER PRIMARY KEY NOT NULL,"
                          "LOGIN        TEXT NOT NULL," 
                          "DATE         INTEGER NOT NULL,"
                          "MESSAGE      TEXT NOT NULL);");
    sql = sqlite3_str_finish(str);
    sqlite3_exec(database, sql, 0, 0, 0);
    sqlite3_free(sql);
}

void mx_create_table_rooms(sqlite3 *database) {
    sqlite3_exec(database, "CREATE TABLE ROOMS("
                       "ID                 INTEGER PRIMARY KEY NOT NULL,"
                       "NAME_ROOM          TEXT                NOT NULL, "
                       "CUSTOMER_LOGIN     TEXT                NOT NULL,"
                       "DATE               INTEGER             NOT NULL);",
                        0, 0, 0);
}
