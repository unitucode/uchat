#include <utils.h>

t_user *mx_get_user_by_login(char *login, sqlite3 *db_user) {
    sqlite3_stmt *stmt;
    t_user *user = mx_malloc(sizeof(t_user));
    int returnvalue;

    sqlite3_prepare_v3(db_user, "SELECT * FROM USER WHERE login = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_ROW) {
        printf("користувача з таким login не існує\n");
        return NULL;
    }
    user->id = sqlite3_column_int(stmt, 0);
    user->login = strdup((const char*)sqlite3_column_text(stmt, 1));
    user->password = strdup((const char*)sqlite3_column_text(stmt, 2));
    user->token = strdup((const char*)sqlite3_column_text(stmt, 3));
    sqlite3_finalize(stmt);
    return user;
}

