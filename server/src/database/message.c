#include "server.h"

/*
 * Function: mx_get_text_message
 * -------------------------------
 * returns the message text from the messages tab
 * 
 * message_id: message id
 * 
 * return: text in gchar
 */
gchar *mx_get_text_message_by_id(sqlite3 *db, guint64 message_id) {
    sqlite3_stmt *stmt;
    gchar *result = NULL;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "select message from messages where message_"
                                "id = ?1", -1, &stmt, 0);
    mx_error_sqlite(rv, "get test message by id");
    sqlite3_bind_int64(stmt, 1, message_id);
    mx_error_sqlite(sqlite3_step(stmt), "get test message by id");
    if (sqlite3_column_text(stmt, 0) != NULL)
        result = strdup((const char*)sqlite3_column_text(stmt, 0));
    return result;
}

/*
 * Function: mx_is_owner_msg
 * -------------------------------
 * checks if the user is the owner of the message
 * 
 * user_id: user id
 * msg_id: message id
 * 
 * return TRUE if user is owner
 */
gboolean mx_is_owner_msg(sqlite3 *db, guint64 user_id, guint64 msg_id) {
    sqlite3_stmt *stmt;
    gint32 rv = 0;
    gboolean is_owner = FALSE;

    rv = sqlite3_prepare_v2(db, "select * from messages where message_id = ?1 "
                                "and user_id = ?2 ", -1, &stmt, NULL);
    mx_error_sqlite(rv, "is owner message");
    sqlite3_bind_int64(stmt, 1, msg_id);
    sqlite3_bind_int64(stmt, 2, user_id);
    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        is_owner = TRUE;
    mx_error_sqlite(rv, "is owner message");
    sqlite3_finalize(stmt);
    return is_owner;
}

/*
 * Function: mx_delete_all_messages
 * -------------------------------
 * delete all messages from this room
 * 
 * room_id: room id
 */
void mx_delete_all_messages(sqlite3 *db, guint64 room_id) {
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gchar *request = NULL;

    sqlite3_str_appendf(sqlite_str, "delete from messages where "
                                    "room_id = %llu",
                        room_id);
    request = sqlite3_str_finish(sqlite_str);
    mx_error_sqlite(sqlite3_exec(db, request, 0, 0, 0), "delete all message");
    sqlite3_free(request);
}

