#include <utils.h>

void mx_insert_room(t_room *room, sqlite3 *db_room) {
    sqlite3_stmt *stmt;
    int returnvalue = 0;

    returnvalue = sqlite3_prepare_v3(db_room,
                       "INSERT INTO roomS(LOGIN, PASSWORD, TOKEN, PERMISSION) \
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
    printf("thread_safe = %d\n", sqlite3_threadsafe());
    sqlite3_prepare_v3(db_room, "SELECT ID FROM roomS WHERE \
                                login = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_ROW) {
        //  mx_elogger(MX_LOG_FILE, LOGERR, "select database table");
    }
    room->id = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    room->login = strdup(login);
    room->token = strdup(token);
    room->password = strdup(password);
    room->permission = 0;
}