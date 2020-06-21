#include "server.h"

gboolean mx_is_owner_msg(sqlite3 *db, guint64 user_id, guint64 msg_id) {
    sqlite3_stmt *stmt;
    gint32 rv = 0;
    gboolean is_owner = false;

    rv = sqlite3_prepare_v2(db, "select * from messages where message_id = ?1 "
                                "and user_id = ?2 ", -1, &stmt, NULL);
    mx_error_sqlite(rv, "step", "is owner");
    sqlite3_bind_int64(stmt, 1, msg_id);
    sqlite3_bind_int64(stmt, 2, user_id);
    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        is_owner = true;
    mx_error_sqlite(rv, "step", "is owner");
    sqlite3_finalize(stmt);
    return is_owner;
}


