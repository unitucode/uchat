#include "utils.h"

// "DELETE FROM ROOMS WHERE NAME_ROOM = ?1"

void mx_delete_room(sqlite3 *database, char *name_room) {
    sqlite3_str *str = sqlite3_str_new(database);
    char *request = NULL;
    int rv = 0;

    sqlite3_str_appendall(str, "DELETE FROM ROOMS WHERE NAME_ROOM = '");
    sqlite3_str_appendall(str, name_room);
    sqlite3_str_appendall(str, "'; DROP TABLE '");
    sqlite3_str_appendall(str, name_room);
    sqlite3_str_appendall(str, "'");
    request = sqlite3_str_finish(str);
    rv = sqlite3_exec(database, request, 0, 0, 0);
    if (rv == SQLITE_ERROR)
        mx_logger(MX_LOG_FILE, LOGWAR, "delete room\n");
    sqlite3_free(request);
}

void mx_delete_user(sqlite3 *database, char *login) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(database, "DELETE FROM USERS WHERE LOGIN = ?1",
        -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    if (rv == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "delete user one");
    if ((rv = sqlite3_step(stmt)) != SQLITE_DONE)
        mx_elogger(MX_LOG_FILE, LOGERR, "delete user");
    sqlite3_finalize(stmt);
}
