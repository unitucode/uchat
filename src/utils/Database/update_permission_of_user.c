#include <utils.h>

void update_permission_of_user(unsigned int permission, char *login, sqlite3 *database) {
    sqlite3_stmt *stmt;
    int returnvalue;

    sqlite3_prepare_v3(database, "UPDATE USER SET PERMISSION = ?1 WHERE token = ?2", -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, permission);
    sqlite3_bind_text(stmt, 2, login, -1, SQLITE_STATIC);
    
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_ROW) {
        printf("error get user !");
    }
    sqlite3_finalize(stmt);
}
