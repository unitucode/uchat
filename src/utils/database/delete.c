#include "utils.h"

void mx_delete_room(sqlite3 *database, int id_room) {
    int rv = 0;
    sqlite3_stmt *stmt;

    rv = sqlite3_prepare_v3(database, "DELETE FROM ROOMS WHERE ID_ROOM = ?1;\
    DELETE FROM MEMBER WHERE ID_ROOM = ?1;\
    DELETE FROM MESSAGE WHERE ID_ROOM = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id_room);
    if (rv == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "delete room");
    if ((rv = sqlite3_step(stmt)) != SQLITE_DONE)
        mx_elogger(MX_LOG_FILE, LOGERR, "delete room");
    sqlite3_finalize(stmt);
}

void mx_delete_user(sqlite3 *database, char *login) {
    int rv = 0;
    sqlite3_stmt *stmt;

    rv = sqlite3_prepare_v3(database, "DELETE FROM USERS WHERE LOGIN = ?1;\
    DELETE FROM MEMBER WHERE LOGIN = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    if (rv == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "delete room");
    if ((rv = sqlite3_step(stmt)) != SQLITE_DONE)
        mx_elogger(MX_LOG_FILE, LOGERR, "delete room");
    sqlite3_finalize(stmt);
}
