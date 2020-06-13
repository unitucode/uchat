#include "server.h"

void update(sqlite3_stmt *stmt, char *new, char *name, char *error) {
    sqlite3_bind_text(stmt, 1, new, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, name, -1, SQLITE_STATIC);
    mx_error_sqlite(sqlite3_step(stmt), "step", error);
    sqlite3_finalize(stmt);
}

void mx_update_permission_of_user(sqlite3 *database, char *login,
                                  unsigned int new) {
    sqlite3_stmt *stmt;
    int rv;

    rv = sqlite3_prepare_v3(database, 
                            "UPDATE USERS SET PERMISSION = ?1 WHERE login = ?2",
                            -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, new);
    sqlite3_bind_text(stmt, 2, login, -1, SQLITE_STATIC);
    mx_error_sqlite(sqlite3_step(stmt), "step", "update permission");
    sqlite3_finalize(stmt);
}

void mx_update_token(sqlite3 *database, char *login, char *new) {
    sqlite3_stmt *stmt;
    int rv;

    rv = sqlite3_prepare_v3(database, 
                       "UPDATE USERS SET TOKEN = ?1 WHERE login = ?2",
                       -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "update token");
    update(stmt, new, login, "update token");
}

void mx_update_description_room_by_id(sqlite3 *db, unsigned long long int id,
                                      char *new) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;

    rv = sqlite3_prepare_v3(db, "update rooms set description = ?1 "
                       "where id = ?2", -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "update description");
    sqlite3_bind_text(stmt, 1, new, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);
    mx_error_sqlite(sqlite3_step(stmt), "step", "update room");
    sqlite3_finalize(stmt);
}

// to delete
void mx_update_description_room(sqlite3 *database, char *name, char *new) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;

    rv = sqlite3_prepare_v3(database, "UPDATE ROOMS SET DESCRIPTION = ?1 "
                       "WHERE NAME_ROOM = ?2", -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "update description");
    update(stmt, new, name, "update room desc");
}

void mx_update_description_user(sqlite3 *database, char *login, char *new) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;
    
    rv = sqlite3_prepare_v3(database, "update users set description = ?1"
                            " where login = ?2", -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "update user");
    update(stmt, new, login, "update user desc");
}
