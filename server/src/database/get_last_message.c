#include "server.h"

gint32 mx_get_type_msg(sqlite3 *db, guint64 id) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;
    gint32 type = 0;

    rv = sqlite3_prepare_v2(db, "select type from messages where message_id"
                                " = ?1", -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "get type msg");
    sqlite3_bind_int64(stmt, 1, id);
    mx_error_sqlite(sqlite3_step(stmt), "step", "get type msg");
    if (sqlite3_column_int64(stmt, 0))
        type = sqlite3_column_int64(stmt, 0);
    else
        type = -1;
    sqlite3_finalize(stmt);
    return type;
}

unsigned long long int mx_get_roomid_by_name(sqlite3 *db, char *name) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;
    unsigned long long int id = 0;

    rv = sqlite3_prepare_v2(db, "select id from rooms where name = ?1 order by date desc",
                            -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    mx_error_sqlite(rv, "prepare", "mx_get_room_id");
    mx_error_sqlite(sqlite3_step(stmt), "step", "mx_get_room_id");
    id = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return id;
}
