#include "utils.h"

void mx_update_permission_of_user(sqlite3 *database, unsigned int permission, char *login) {
    sqlite3_stmt *stmt;
    int returnvalue;

    sqlite3_prepare_v3(database, "UPDATE USERS SET PERMISSION = ?1 WHERE login = ?2", -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, permission);
    sqlite3_bind_text(stmt, 2, login, -1, SQLITE_STATIC);
    
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_DONE) {
        mx_logger(MX_LOG_FILE, LOGWAR, "error update permission");
    }
    sqlite3_finalize(stmt);
}
