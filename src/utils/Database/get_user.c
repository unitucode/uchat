#include <utils.h>

t_user *mx_get_user(char *login, sqlite3 *db_user) {
    sqlite3_stmt *stmt;
    sqlite3_str *new = sqlite3_str_new(db_user);
    t_user *user = mx_malloc(sizeof(t_user));
    int returnvalue;
    char *sqlstr = NULL;

    sqlite3_str_appendf(new, "SELECT * from USER WHERE login = \'%s\'", login);
    sqlstr = sqlite3_str_finish(new);
    sqlite3_prepare(db_user, sqlstr, -1, &stmt, NULL);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_ROW) {
        printf("користувача з таким логіном не існує\n");
        return NULL;
    }
    user->id = sqlite3_column_int(stmt, 0);
    user->login = strdup((const char*)sqlite3_column_text(stmt, 2));
    user->token = strdup((const char*)sqlite3_column_text(stmt, 1));
    user->password = strdup((const char*)sqlite3_column_text(stmt, 3));
    sqlite3_finalize(stmt);
    return user;
}
