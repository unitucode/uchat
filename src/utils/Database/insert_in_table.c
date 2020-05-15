#include <utils.h>

t_room *mx_insert_room(char *customer, char *name_room, sqlite3 *database) {
    sqlite3_stmt *stmt;
    int returnvalue = 0;

    returnvalue = sqlite3_prepare_v3(database,
                       "INSERT INTO ROOMS(NAME_ROOM, CUSTOMER_LOGIN) \
                       VALUES(?1, ?2);", -1, 0, &stmt, NULL);
    if (returnvalue == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
     sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
     sqlite3_bind_text(stmt, 2, customer, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_DONE)
        //  mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_prepare_v3(database, "SELECT ID FROM ROOMS WHERE \
                                NAME_ROOM = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_ROW)
        //  mx_elogger(MX_LOG_FILE, LOGERR, "select database table");
    sqlite3_finalize(stmt);
    return mx_get_room(name_room, database);
}


t_user *mx_insert_user(char *login, char *password,
                       char *token, sqlite3 *database) {
    sqlite3_stmt *stmt;
    int returnvalue = 0;

    returnvalue = sqlite3_prepare_v3(database,
                       "INSERT INTO USERS(LOGIN, PASSWORD, TOKEN, PERMISSION) \
                       VALUES(?1, ?2, ?3, 0);", -1, 0, &stmt, NULL);
    if (returnvalue == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
     sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
     sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
     sqlite3_bind_text(stmt, 3, token, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_DONE)
        //  mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_finalize(stmt);
    return mx_get_user_by_login(login, database);
}

void mx_insert_memeber(char *login, int id_room, sqlite3 *database) {
    sqlite3_stmt *stmt;
    int returnvalue = 0;

    returnvalue = sqlite3_prepare_v3(database, "INSERT INTO MEMEBER(ID, LOGIN) VALUES(?1, ?2);", -1, 0, &stmt, NULL);
    if (returnvalue == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_bind_int(stmt, 1, id_room);
    sqlite3_bind_text(stmt, 2, login, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_DONE)
        //  mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_finalize(stmt);
}

void mx_insert_message(char *login, char *json, sqlite3 *database) {
    sqlite3_stmt *stmt;
    int returnvalue = 0;

    returnvalue = sqlite3_prepare_v3(database, "INSERT INTO MESSAGE(LOGIN, JSON)VALUES(?1, ?2);", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, json, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_DONE)
        //  mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_finalize(stmt);
}
