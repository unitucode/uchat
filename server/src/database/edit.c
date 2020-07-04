#include "server.h"

/*
 * Function: mx_edit_room_name_by_id
 * -------------------------------
 * changes the name of the room
 * 
 * id: room_id
 * new_name: new room name
 */
void mx_edit_room_name_by_id(sqlite3 *db, guint64 id, gchar *new_name) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "update rooms set name = ?1 "
                                "where id = ?2", -1,
                            &stmt, NULL);
    mx_error_sqlite(rv, "edit room name by id");
    sqlite3_bind_text(stmt, 1, new_name, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 2, id);
    mx_error_sqlite(sqlite3_step(stmt), "edit room name by id");
    sqlite3_finalize(stmt);
}

/*
 * Function: mx_edit_user_name_by_id
 * -------------------------------
 * changes the name of the user
 * 
 * id: user_id
 * new_name: new user name
 */
void mx_edit_user_name_by_id(sqlite3 *db, guint64 id, gchar *new_name) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "update users set login = ?1 "
                                "where id = ?2", -1,
                            &stmt, NULL);
    mx_error_sqlite(rv, "edit_user_name_by_id");
    sqlite3_bind_text(stmt, 1, new_name, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 2, id);
    mx_error_sqlite(sqlite3_step(stmt), "edit_user_name_by_id");
    sqlite3_finalize(stmt);
}

static void update_power_message(sqlite3 *db, guint64 power, guint64 id) {
    gint32 rv = SQLITE_OK;
    guint64 room_id = 0;
    sqlite3_stmt *stmt;

    rv = sqlite3_prepare_v2(db, "select room_id, power from messages "
                                "where message_id = ?1", -1, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, id);
    mx_error_sqlite(sqlite3_step(stmt), "update power message");
    if (sqlite3_column_int64(stmt, 0))
        room_id = sqlite3_column_int64(stmt, 0);
    if (sqlite3_column_int64(stmt, 1))
        power += sqlite3_column_int64(stmt, 1);
    sqlite3_finalize(stmt);
    rv = sqlite3_prepare_v2(db, "update messages set power = ?1 where "
                                "message_id = ?2", -1, &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, power);
    sqlite3_bind_int64(stmt, 2, id);
    mx_error_sqlite(sqlite3_step(stmt), "update power message");
    sqlite3_finalize(stmt); 
    mx_db_update_room_power(db, power, room_id);
}
/*
 * Function: mx_edit_message_by_id
 * -------------------------------
 * changes the message
 * 
 * id: message id
 * new: new message
 */
void mx_edit_message_by_id(sqlite3 *db, guint64 id, gchar *new) {
    sqlite3_str *str = sqlite3_str_new(db);
    sqlite3_stmt *stmt;
    gchar *request = NULL;

    sqlite3_str_appendf(str, "update messages set message = ?1 where "
                             "message_id = %lu",
                        id);
    request = sqlite3_str_finish(str);
    mx_error_sqlite(sqlite3_prepare(db, request, -1, &stmt, NULL), 
                    "edit message by id");
    sqlite3_bind_text(stmt, 1, new, -1, SQLITE_STATIC);
    mx_error_sqlite(sqlite3_step(stmt), "edit message by id");
    sqlite3_free(request);
    sqlite3_finalize(stmt);
    update_power_message(db, strlen(new), id);
}

/*
 * Function: mx_edit_type_member
 * -------------------------------
 * changes permission of user in this room
 * 
 * room_id: room id
 * user_id: user id
 * new type: new permission
 */
void mx_edit_type_member(sqlite3 *db, guint64 room_id, guint64 user_id,
                         gint8 new_type) {
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gchar *request = NULL;
    gint32 rv = SQLITE_OK;

    sqlite3_str_appendf(sqlite_str, "update members set permission = %d where "
                                    "room_id = %llu and user_id = %llu",
                        new_type, room_id, user_id);
    request = sqlite3_str_finish(sqlite_str);
    rv = sqlite3_exec(db, request, 0, 0, 0);
    mx_error_sqlite(rv, "edit type member");
    sqlite3_free(request);
}
