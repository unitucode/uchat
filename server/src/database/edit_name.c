#include "server.h"

void mx_edit_name_user(sqlite3 *database, char *login, char *new) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;

    rv = sqlite3_prepare_v3(database, "UPDATE USERS SET LOGIN = ?1"
                                      " WHERE LOGIN = ?2",
                            -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "rename user");
    update(stmt, new, login, "rename user");
}

void mx_edit_name_room(sqlite3 *database, char *name_room, char *new) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;
    char *request = NULL;
    sqlite3_str *str = sqlite3_str_new(database);

    sqlite3_str_appendall(str, "ALTER TABLE '");
    sqlite3_str_appendall(str, name_room);
    sqlite3_str_appendall(str, "' RENAME TO '");
    sqlite3_str_appendall(str, new);
    sqlite3_str_appendall(str, "'");
    request = sqlite3_str_finish(str);
    rv = sqlite3_prepare_v3(database, "UPDATE ROOMS SET NAME_ROOM = ?1"
                            " WHERE NAME_ROOM = ?2", -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "rename room");
    update(stmt, new, name_room, "rename room");
    rv = sqlite3_prepare_v3(database, request, -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "rename room");
    mx_error_sqlite(sqlite3_step(stmt), "step", "edit name room");
    sqlite3_free(request);
    sqlite3_finalize(stmt);
}
