#include "server.h"

/*
 * Function: 
 * 
 */

gchar *mx_get_text_message_by_id(sqlite3 *db, guint64 message_id) {
    sqlite3_stmt *stmt;
    gchar *result = NULL;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "select message from messages where message_id "
                           "= ?1", -1, &stmt, 0);
    printf("rv = %d\n", rv);
    mx_error_sqlite(rv, "prepare", "get text msg");
    sqlite3_bind_int64(stmt, 1, message_id);
    mx_error_sqlite(sqlite3_step(stmt), "step", "get text msg");
    if (sqlite3_column_text(stmt, 0) != NULL) {
        result = strdup((const char*)sqlite3_column_text(stmt, 0));
        printf("Ok\n");
    }
    return result;
}


/*
 * Function: 
 * 
 */

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

/*
 * Function: 
 * 
 */

void mx_delete_all_messages(sqlite3 *db, guint64 room_id) {
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gchar *request = NULL;

    sqlite3_str_appendf(sqlite_str, "delete from messages where "
                                    "room_id = %llu",
                        room_id);
    request = sqlite3_str_finish(sqlite_str);
    mx_error_sqlite(sqlite3_exec(db, request, 0, 0, 0), "exec", "del all msg");
    sqlite3_free(request);
}

