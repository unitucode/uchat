#include "server.h"

// to delete
void mx_delete_room(sqlite3 *database, char *name_room) {
    sqlite3_str *str = sqlite3_str_new(database);
    char *request = NULL;
    int rv = 0;

    sqlite3_str_appendall(str, "DELETE FROM ROOMS WHERE NAME = '");
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

void mx_delete_room_by_id(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
    int rv = 0;
    sqlite3_str *str = sqlite3_str_new(db);
    char *request = NULL;

    rv = sqlite3_prepare_v2(db, "delete from rooms where id = ?1", 
                            -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare1", "delete room by id");
    sqlite3_bind_int(stmt, 1, id);
    mx_error_sqlite(sqlite3_step(stmt), "step1", "delete room by id");
    sqlite3_finalize(stmt);
    sqlite3_str_appendall(str, "drop table ");
    sqlite3_str_appendf(str, "room%d", id);
    request = sqlite3_str_finish(str);
    rv = sqlite3_prepare_v2(db, request, -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "drop room");
    mx_error_sqlite(sqlite3_step(stmt), "step", "drop room");
    sqlite3_free(request);
    sqlite3_finalize(stmt);
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

void mx_delete_message(sqlite3 *database, int id, int id_message) {
    char *request = NULL;
    sqlite3_stmt *stmt;
    sqlite3_str *str = sqlite3_str_new(database);
    int rv = SQLITE_OK;

    sqlite3_str_appendall(str, "DELETE FROM ");
    sqlite3_str_appendf(str, "room%d", id);
    sqlite3_str_appendall(str, " WHERE ID_MESSAGE = ?1");
    request = sqlite3_str_finish(str);
    rv = sqlite3_prepare_v3(database, request, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id_message);
    mx_error_sqlite(rv, "prepare", "delete message");
    mx_error_sqlite(sqlite3_step(stmt), "step", "delete message");
    sqlite3_free(request);
    sqlite3_finalize(stmt);
}
