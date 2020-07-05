#include "server.h"

/*
 * Function: mx_edit_permission_of_user
 * -------------------------------
 * changes the rights of this user in the bathroom
 * 
 * user_id: user id
 * room_id: room id
 * new: new user permission
 */
void mx_edit_permission_of_user(sqlite3 *db, guint64 user_id, guint64 room_id,
                                gint8 new) {
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gchar *request = NULL;

    sqlite3_str_appendf(sqlite_str, "update members set permission = %d where"
                                    " id = %llu and where room_id = %llu",
                        new, user_id, room_id);
    request = sqlite3_str_finish(sqlite_str);
    mx_error_sqlite(sqlite3_exec(db, request, 0, 0, 0),
                                 "mx_edit_permission_of_user");
}

/*
 * Function: mx_edit_token
 * -------------------------------
 * changes the user's token
 * 
 * user_id: user id
 * new: new user token
 */
void mx_edit_token(sqlite3 *db, guint64 user_id, gchar *new) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "update users set token = ?1 where "
                                "id = ?2", -1, &stmt, NULL);
    mx_error_sqlite(rv, "edit token");
    sqlite3_bind_text(stmt, 1, new, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 2, user_id);
    mx_error_sqlite(sqlite3_step(stmt), "edit token");
    sqlite3_finalize(stmt);
}

/*
 * Function: mx_edit_desc_room_by_id
 * -------------------------------
 * changes the room description
 * 
 * room_id: room id
 * new: new description of room
 */
void mx_edit_desc_room_by_id(sqlite3 *db, guint64 room_id, gchar *new) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "update rooms set desc = ?1 "
                                "where id = ?2", -1, &stmt, NULL);
    mx_error_sqlite(rv, "mx_edit_desc_room_by_id");
    sqlite3_bind_text(stmt, 1, new, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, room_id);
    mx_error_sqlite(sqlite3_step(stmt), "mx_edit_desc_room_by_id");
    sqlite3_finalize(stmt);
}

/*
 * Function: mx_edit_desc_user
 * -------------------------------
 * changes the user description
 * 
 * user_id: user id
 * new: new description of user
 */
void mx_edit_desc_user(sqlite3 *db, guint64 user_id, gchar *new) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;
    
    rv = sqlite3_prepare_v2(db, "update users set desc = ?1" 
                                " where id = ?2", -1, &stmt, NULL);
    mx_error_sqlite(rv, "mx_edit_desc_user");
    sqlite3_bind_text(stmt, 1, new, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 2, user_id);
    mx_error_sqlite(sqlite3_step(stmt), "mx_edit_desc_user");
    sqlite3_finalize(stmt);
}

