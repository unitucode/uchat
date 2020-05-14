#include <utils.h>

t_user *mx_insert_user(char *login, char *password,
                       char *token, sqlite3 *db_user) {
    sqlite3_stmt *stmt;
    t_user *user = malloc(sizeof(t_user));
    int returnvalue = 0;

    returnvalue = sqlite3_prepare_v3(db_user,
                       "INSERT INTO USERS(LOGIN, PASSWORD, TOKEN, PERMISSION) \
                       VALUES(?1, ?2, ?3, ?4);", -1, 0, &stmt, NULL);
    if (returnvalue == SQLITE_ERROR) {     
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    }
     sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
     sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
     sqlite3_bind_text(stmt, 3, token, -1, SQLITE_STATIC);
     sqlite3_bind_int(stmt, 4, 0);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_DONE) {
        //  mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    }
    sqlite3_finalize(stmt);
    user->login = strdup(login);
    user->token = strdup(token);
    user->password = strdup(password);
    user->permission = 0;
    return user;
}
