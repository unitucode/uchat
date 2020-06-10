#include "server.h"

t_db_message *mx_insert_message_into_db(sqlite3 *database, char *message_str,
                                     char *login, char *name_room) {
    sqlite3_stmt *stmt;
    char *request = NULL;
    int rv = 0;
    sqlite3_str *str = sqlite3_str_new(database);

    sqlite3_str_appendall(str, "INSERT INTO '" );
    sqlite3_str_appendall(str, name_room);
    sqlite3_str_appendall(str, "' (LOGIN, DATE, MESSAGE) VALUES(?1, ?2, ?3);");
    request = sqlite3_str_finish(str);
    if ((rv = sqlite3_prepare_v3(database, request, -1, 0, &stmt, NULL)) == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert message into database");
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, (long int)time(NULL));
    sqlite3_bind_text(stmt, 3, message_str, -1, SQLITE_STATIC);
    if ((rv = sqlite3_step(stmt)) != SQLITE_DONE)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert message into database");
    sqlite3_finalize(stmt);
    sqlite3_free(request);
    return mx_get_last_message(database, mx_get_roomid_by_name(name_room));
}

t_db_room *mx_insert_room_into_db(sqlite3 *database, char *name_room, 
                            char *customer) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(database,
                            "INSERT INTO ROOMS(NAME, CUSTOMER_LOGIN, DATE,"
                            " DESCRIPTION) VALUES(?1, ?2, ?3, '');",
                            -1, 0, &stmt, NULL);
    if (rv == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert room into db one %d\n", rv);
    sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, customer, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, (long int)time(NULL));
    if ((rv = sqlite3_step(stmt)) != SQLITE_DONE) {
        mx_elogger(MX_LOG_FILE, LOGERR, "insert room into db two %d\n", rv);
    }
    sqlite3_finalize(stmt);
    mx_create_table_room(database, name_room);
    return mx_get_room(database, name_room);
}

t_db_user *mx_insert_user_into_db(sqlite3 *database, char *login,
                            char *pass, char *token) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(database,
        "INSERT INTO USERS(LOGIN, PASSWORD, TOKEN, PERMISSION, DATE, " 
        "DESCRIPTION) VALUES(?1, ?2, ?3, 0, ?4, '');",
                            -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "insert user");
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pass, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, token, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, (long int)time(NULL));
    mx_error_sqlite(sqlite3_step(stmt), "step", "insert user");
    sqlite3_finalize(stmt);
    return mx_get_user_by_login(database, login);
}

void mx_insert_member_into_db(sqlite3 *database, 
                           char *login, char *name_room) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(database,
         "INSERT INTO MEMBER(NAME_ROOM, LOGIN)VALUES(?1, ?2);",
         -1, 0, &stmt, NULL);
    if (rv == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, login, -1, SQLITE_STATIC);
    if ((rv = sqlite3_step(stmt)) != SQLITE_DONE)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_finalize(stmt);
}
