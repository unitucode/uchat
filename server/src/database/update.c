#include "server.h"

void mx_edit_permission_of_user(sqlite3 *db, guint64 user_id, guint64 room_id,
                                  gint8 new) {
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gchar *request = NULL;

    sqlite3_str_appendf(sqlite_str, "update members set permission = %d where"
                                    " user_id = %llu and where room_id = %llu", 
                        new, user_id, room_id);
    request = sqlite3_str_finish(sqlite_str);
    mx_error_sqlite(sqlite3_exec(db, request, 0, 0, 0), "exec",
                     "update permission");
}

void mx_edit_token(sqlite3 *db, guint64 user_id, gchar *new) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "update users set token = ?1 where "
                                "user_id = ?2", -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "update token");
    sqlite3_bind_text(stmt, 1, new, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 2, user_id);
    mx_error_sqlite(sqlite3_step(stmt), "step", "update token");
    sqlite3_finalize(stmt);
}

void mx_edit_desc_room_by_id(sqlite3 *db, guint64 room_id, gchar *new) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "update rooms set desc = ?1 "
                                "where id = ?2", -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "update description");
    sqlite3_bind_text(stmt, 1, new, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, room_id);
    mx_error_sqlite(sqlite3_step(stmt), "step", "update room");
    sqlite3_finalize(stmt);
}

void mx_edit_desc_user(sqlite3 *db, guint64 user_id, gchar *new) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;
    
    rv = sqlite3_prepare_v2(db, "update users set desc = ?1" 
                                " where user_id = ?2", -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "update user");
    sqlite3_bind_text(stmt, 1, new, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 2, user_id);
    mx_error_sqlite(sqlite3_step(stmt), "step", "update desc user");
    sqlite3_finalize(stmt);
}

