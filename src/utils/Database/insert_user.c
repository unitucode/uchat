#include <utils.h>

t_user *mx_insert_user(char *login, char *password, char *token, sqlite3 *db_user) {
    sqlite3_stmt *stmt;
    t_user *user = malloc(sizeof(t_user));
    int returnvalue = 0;

    sqlite3_prepare_v3(db_user, "INSERT INTO USER(LOGIN, PASSWORD, TOKEN) \
                                 VALUES(?1, ?2, ?3);", -1, 0, &stmt, NULL);
     sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
     sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
     sqlite3_bind_text(stmt, 3, token, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_DONE) {
        //  mx_elogger(MX_LOG_FILE, LOGWAR, "error insert database table");
    }
    printf("thread_safe = %d\n", sqlite3_threadsafe());
    sqlite3_prepare_v3(db_user, "SELECT ID from USER WHERE login = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
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
