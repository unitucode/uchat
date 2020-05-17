#include "utils.h"

void mx_create_table_users(sqlite3 *database) {
    int tmp = 0;

    if ((tmp = sqlite3_exec(database,  "CREATE TABLE USERS(\
                        LOGIN          TEXT  UNIQUE   NOT NULL,\
                        PASSWORD       TEXT           NOT NULL,\
                        TOKEN          TEXT           NOT NULL,\
                        PERMISSION     INTEGER        NOT NULL);", 0, 0, 0)) != SQLITE_OK) {
        // printf("tmp create -> %d\n", tmp);
        // mx_elogger(MX_LOG_FILE, LOGWAR, "error create database table");
    }
}

void mx_create_table_member(sqlite3 *database) {
    int tmp = 0;

    if ((tmp = sqlite3_exec(database, "CREATE TABLE MEMBER("\
                        "ID_ROOM          INTEGER NOT NULL,"\
                        "LOGIN            TEXT    NOT NULL);", 0, 0, 0)) != SQLITE_OK) {
        // printf("tmp create -> %d\n", tmp);
        // mx_elogger(MX_LOG_FILE, LOGWAR, "error create database table");
    }
}

void mx_create_table_message(sqlite3 *database) {
    int tmp = 0;

    if ((tmp = sqlite3_exec(database, "CREATE TABLE MESSAGE("  \
                         "ID_MESSAGE    INTEGER PRIMARY KEY NOT NULL," \
                         "LOGIN         TEXT                NOT NULL," \
                         "DATE          INTEGER             NOT NULL," \
                         "JSON          TEXT                NOT NULL);", 0, 0, 0)) != SQLITE_OK) {
        // printf("tmp create -> %d\n", tmp);
        // mx_elogger(MX_LOG_FILE, LOGWAR, "error create database table");
    }
}

void mx_create_table_rooms(sqlite3 *database) {
    int tmp = 0;

    if ((tmp = sqlite3_exec(database, "CREATE TABLE ROOMS("  \
                       "ID                 INTEGER PRIMARY KEY NOT NULL," \
                       "NAME_ROOM          TEXT                NOT NULL, " \
                       "CUSTOMER_LOGIN     TEXT                NOT NULL);", 0, 0, 0)) != SQLITE_OK) {
        // printf("tmp create -> %d\n", tmp);
        // mx_elogger(MX_LOG_FILE, LOGWAR, "error create database table");
    }
}
