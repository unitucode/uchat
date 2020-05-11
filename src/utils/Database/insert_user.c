#include <utils.h>

t_user *mx_insert_user(char *login, char *password, char *token, sqlite3 *db_user) {
    char *sqlstr = NULL;
    sqlite3_str *new = sqlite3_str_new(db_user);
    sqlite3_stmt *stmt;
    t_user *user = malloc(sizeof(t_user));
    int returnvalue = 0;

    sqlite3_str_appendf(new, "INSERT INTO USER(LOGIN, PASSWORD, TOKEN) VALUES(\'%s\',\'%s\',\'%s\');", login, password, token);
    sqlstr = sqlite3_str_finish(new);
    if ((returnvalue = sqlite3_exec(db_user, sqlstr, 0, 0, 0)) != SQLITE_OK) {
        //  mx_elogger(MX_LOG_FILE, LOGWAR, "error insert database table");
    }
    new = sqlite3_str_new(db_user);
    sqlite3_str_appendf(new, "SELECT ID from USER WHERE login = \'%s\'", login);
    sqlstr  = sqlite3_str_finish(new);
    sqlite3_prepare(db_user, sqlstr, -1, &stmt, NULL);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_ROW) {
        //  mx_elogger(MX_LOG_FILE, LOGWAR, "error select database table");
    }
    user->id = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    user->login = strdup(login);
    user->token = strdup(token);
    user->password = strdup(password);
    return user;
}
