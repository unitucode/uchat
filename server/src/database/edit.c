#include "server.h"

void mx_edit_room_name_by_id(sqlite3 *db, guint64 id, gchar *new_name) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "update rooms set name = ?1 where id = ?2", -1,
                            &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "edit name room");
    sqlite3_bind_text(stmt, 1, new_name, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 2, id);
    mx_error_sqlite(sqlite3_step(stmt), "step", "edit room name");
    sqlite3_finalize(stmt);
}

void mx_edit_user_name_by_id(sqlite3 *db, guint64 id, gchar *new_name) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "update users set login = ?1 where id = ?2", -1,
                            &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "edit name user");
    sqlite3_bind_text(stmt, 1, new_name, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 2, id);
    mx_error_sqlite(sqlite3_step(stmt), "step", "edit room user");
    sqlite3_finalize(stmt);
}

void mx_edit_message_by_id(sqlite3 *db, guint64 id, gchar *new) {
    sqlite3_str *str = sqlite3_str_new(db);
    sqlite3_stmt *stmt;
    gchar *request = NULL;

    sqlite3_str_appendf(str, "update messages set message = ?1 where "
                             "message_id = %lu",
                        id);
    request = sqlite3_str_finish(str);
    mx_error_sqlite(sqlite3_prepare(db, request, -1, &stmt, NULL), "prepare",
                    "edit message");
    sqlite3_bind_text(stmt, 1, new, -1, SQLITE_STATIC);
    mx_error_sqlite(sqlite3_step(stmt), "step", "edit message");
    sqlite3_free(request);
    sqlite3_finalize(stmt);
}
