#include "utils.h"

t_room *mx_insert_room(sqlite3 *database, char *customer, char *name_room) {
    sqlite3_stmt *stmt;
    int returnvalue = 0;

    returnvalue = sqlite3_prepare_v3(database, "INSERT INTO ROOMS(NAME_ROOM, CUSTOMER_LOGIN) VALUES(?1, ?2);", -1, 0, &stmt, NULL);
    if (returnvalue == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
     sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
     sqlite3_bind_text(stmt, 2, customer, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_DONE)
         mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_finalize(stmt);
    return mx_get_room(database, name_room);
}


t_user *mx_insert_user(sqlite3 *database, char *login, char *password, char *token) {
    sqlite3_stmt *stmt;
    int returnvalue = 0;

    returnvalue = sqlite3_prepare_v3(database, "INSERT INTO USERS(LOGIN, PASSWORD, TOKEN, PERMISSION)VALUES(?1, ?2, ?3, 0);", -1, 0, &stmt, NULL);
    if (returnvalue == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
     sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
     sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
     sqlite3_bind_text(stmt, 3, token, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_DONE)
         mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_finalize(stmt);
    return mx_get_user_by_login(database, login);
}

void mx_insert_memeber(sqlite3 *database, int id_room, char *login) {
    sqlite3_stmt *stmt;
    int returnvalue = 0;

    returnvalue = sqlite3_prepare_v3(database, "INSERT INTO MEMBER(ID_ROOM, LOGIN)VALUES(?1, ?2);", -1, 0, &stmt, NULL);
    if (returnvalue == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_bind_int(stmt, 1, id_room);
    sqlite3_bind_text(stmt, 2, login, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_DONE)
         mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_finalize(stmt);
}

void mx_insert_message(sqlite3 *database, char *login, long long date, char *json) {
    sqlite3_stmt *stmt;
    int returnvalue = 0;

    returnvalue = sqlite3_prepare_v3(database, "INSERT INTO MESSAGE(LOGIN, DATE, JSON)VALUES(?1, ?2, ?3);", -1, 0, &stmt, NULL);
    if (returnvalue == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, date);
    sqlite3_bind_text(stmt, 3, json, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_DONE)
         mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_finalize(stmt);
}
