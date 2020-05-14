#include <utils.h>

t_room *mx_insert_room(char *customer, char *name_room, sqlite3 *db_room) {
    sqlite3_stmt *stmt;
    int returnvalue = 0;
    t_room *room = malloc(sizeof(t_room));

    returnvalue = sqlite3_prepare_v3(db_room,
                       "INSERT INTO ROOMS(NAME_ROOM, CUSTOMER_LOGIN) \
                       VALUES(?1, ?2);", -1, 0, &stmt, NULL);
    if (returnvalue == SQLITE_ERROR) {     
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    }
     sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
     sqlite3_bind_text(stmt, 2, customer, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_DONE) {
        //  mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    }
    sqlite3_prepare_v3(db_room, "SELECT ID FROM ROOMS WHERE \
                                NAME_ROOM = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_ROW) {
        //  mx_elogger(MX_LOG_FILE, LOGERR, "select database table");
    }
    room->id = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    room->name = name_room;
    room->customer = customer;
    return room;
}
