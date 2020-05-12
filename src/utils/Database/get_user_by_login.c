#include <utils.h>

t_user *mx_get_user_by_login(char *login, sqlite3 *db_user) {
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db_user, "SELECT * FROM USER WHERE login = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    return for_get_user(stmt);
}

