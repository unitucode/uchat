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

void mx_edit_name_room(sqlite3 *database, unsigned long long int id, char *new) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;

    rv = sqlite3_prepare_v3(database, "UPDATE ROOMS SET NAME = ?1"
                                      " WHERE ID = ?2", -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "rename room");
    sqlite3_bind_text(stmt, 1, new, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);
    mx_error_sqlite(sqlite3_step(stmt), "step", "edit_name room");
    sqlite3_finalize(stmt);
}
