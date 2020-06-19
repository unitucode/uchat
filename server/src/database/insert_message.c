#include "server.h"

static void get_id_msg(sqlite3 *db, t_db_message *message) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "select message_id from messages where room_id = ?1 and"
                                " date = ?2", -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "get id msg");
    sqlite3_bind_int64(stmt, 1, message->room_id);
    sqlite3_bind_int64(stmt, 2, message->date);
    mx_error_sqlite(sqlite3_step(stmt), "step", "get id msg");
    message->message_id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
}

void mx_insert_message(sqlite3 *db, t_db_message *message) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    message->date = mx_get_time();
    message->status = STATUS_MSG_START;
    rv = sqlite3_prepare_v2(db, "insert into messages(room_id, user_id, date, "
                                "type, message, size, name, status)values(?1, "
                                "?2, ?3, ?4, ?5, ?6, ?7, ?8)", -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "insert_msg_file");
    sqlite3_bind_int64(stmt, 1, message->user_id);
    sqlite3_bind_int64(stmt, 2, message->room_id);
    sqlite3_bind_int64(stmt, 3, message->date);
    sqlite3_bind_int(stmt, 4, message->type);
    sqlite3_bind_text(stmt, 5, message->message, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 6, message->size);
    sqlite3_bind_text(stmt, 7, message->name_file, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 8, message->status);
    mx_error_sqlite(sqlite3_step(stmt), "step", "insert_msg_file");
    sqlite3_finalize(stmt);
    get_id_msg(db, message);
}
