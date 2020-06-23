#include "server.h"


void mx_delete_message_by_id(sqlite3 *db, guint64 id) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "delete from messages where message_id "
                                "= ?1", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    mx_error_sqlite(rv, "prepare", "delete message");
    mx_error_sqlite(sqlite3_step(stmt), "step", "delete message");
    sqlite3_finalize(stmt);
}

void mx_delete_room_by_id(sqlite3 *db, guint64 room_id) {
    gchar *request = NULL;
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gint32 rv = SQLITE_OK;

    sqlite3_str_appendf(sqlite_str, "delete from rooms where id = %llu; delete "
                                    "from messages where room_id = %llu; "
                                    "delete from members where room_id = %llu",
                        room_id, room_id, room_id);
    request = sqlite3_str_finish(sqlite_str);
    rv = sqlite3_exec(db, request, 0, 0, 0);
    mx_error_sqlite(rv, "exec", "delete room");
    sqlite3_free(request);
}

void mx_delete_user_by_id(sqlite3 *db, guint64 id) {
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gint32 rv = SQLITE_OK;
    gchar *request = NULL;

    sqlite3_str_appendf(sqlite_str, "delete from users where id = %lu; delete "
                                    "from contacts where user_id = %lu and whe"
                                    "re user_contact_id = %lu;", id, id, id);
    request = sqlite3_str_finish(sqlite_str);
    rv = sqlite3_exec(db, request, 0, 0, 0);
    mx_error_sqlite(rv, "exec", "delete user");
    sqlite3_free(request);
}
