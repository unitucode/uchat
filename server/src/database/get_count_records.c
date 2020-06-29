#include "server.h"

/*
 * Function: 
 * 
 */

guint64 mx_get_count_messages(sqlite3 *db, guint64 id) {
    sqlite3_stmt *stmt;
    sqlite3_str *str = sqlite3_str_new(db);
    gchar *request = NULL;
    gint32 rv = SQLITE_OK;
    guint64 count = 0;

    sqlite3_str_appendf(str, "select count() from messages "
                             "where room_id = %lu", id);
    request = sqlite3_str_finish(str);
    rv = sqlite3_prepare_v2(db, request, -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "count messages");
    mx_error_sqlite(sqlite3_step(stmt), "step", "count messages");
    count = sqlite3_column_int64(stmt, 0);
    sqlite3_free(request);
    sqlite3_finalize(stmt);
    return count;
}

/*
 * Function: 
 * 
 */

guint64 mx_get_count_rooms(sqlite3 *db) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;
    guint64 count;

    rv = sqlite3_prepare_v2(db, "select count() from rooms", -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "count rooms");
    mx_error_sqlite(sqlite3_step(stmt), "step", "count rooms");
    count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

/*
 * Function: 
 * 
 */

guint64 mx_get_count_users(sqlite3 *db) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;
    guint64 count;

    rv = sqlite3_prepare_v2(db, "select count() from users", -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "get count users");
    mx_error_sqlite(sqlite3_step(stmt), "step", "get count users");
    count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}
