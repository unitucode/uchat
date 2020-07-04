#include "server.h"

/*
 * Function: mx_delete_message_by_id
 * -------------------------------
 * delete message
 * 
 * db: closed database structure
 * id: message id
 */
void mx_delete_message_by_id(sqlite3 *db, guint64 id) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "delete from messages where message_id "
                                "= ?1", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    mx_error_sqlite(rv, "delete_message");
    mx_error_sqlite(sqlite3_step(stmt), "delete_message");
    sqlite3_finalize(stmt);
}

/*
 * Function: mx_delete_room_by_id
 * -------------------------------
 * delete room and members with the room 
 * and messages in the room
 * 
 * db: closed database structure
 * id: room_id
 */
void mx_delete_room_by_id(sqlite3 *db, guint64 room_id) {
    gchar *request = NULL;
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gint32 rv = SQLITE_OK;

    sqlite3_str_appendf(sqlite_str, "delete from rooms where id = %llu;"
                                    "delete from members where room_id = %llu;"
                                    "delete from messages where room_id "
                                    "= %llu",
                        room_id, room_id, room_id);
    request = sqlite3_str_finish(sqlite_str);
    rv = sqlite3_exec(db, request, 0, 0, 0);
    mx_error_sqlite(rv, "delte room by id");
    sqlite3_free(request);
}

/*
 * Function: mx_delete_user_by_id
 * -------------------------------
 * delete user and contacts with user
 * 
 * db: closed database structure
 * id: user_id
 */
void mx_delete_user_by_id(sqlite3 *db, guint64 id) {
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gint32 rv = SQLITE_OK;
    gchar *request = NULL;

    sqlite3_str_appendf(sqlite_str, "delete from users where id = %lu; delete "
                                    "from contacts where user_id = %lu and whe"
                                    "re user_contact_id = %lu;", id, id, id);
    request = sqlite3_str_finish(sqlite_str);
    rv = sqlite3_exec(db, request, 0, 0, 0);
    mx_error_sqlite(rv, "delete user by id");
    sqlite3_free(request);
}
