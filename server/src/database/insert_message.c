#include "server.h"

/*
 * Function: 
 * 
 */
static void get_id_msg(sqlite3 *db, t_db_message *message) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "select message_id from messages where "
                                "room_id = ?1 and date = ?2",
                            -1, &stmt, NULL);
    mx_error_sqlite(rv, "get message id");
    sqlite3_bind_int64(stmt, 1, message->room_id);
    sqlite3_bind_int64(stmt, 2, message->date);
    mx_error_sqlite(sqlite3_step(stmt), "get message id");
    message->message_id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
}

/*
 * Function: 
 * 
 */
static void sqlite_bind_msg(sqlite3_stmt *stmt, t_db_message *message) {
    sqlite3_bind_int64(stmt, 1, message->user_id);
    sqlite3_bind_int64(stmt, 2, message->room_id);
    sqlite3_bind_int64(stmt, 3, message->date);
    sqlite3_bind_int(stmt, 4, message->type);
    sqlite3_bind_text(stmt, 5, message->message, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 6, message->file_size);
    sqlite3_bind_text(stmt, 7, message->file_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 8, message->status);
    sqlite3_bind_int64(stmt, 9, message->power);
}

/*
 * Function: mx_insert_message
 * -------------------------------
 * makes an entry in the database in the messages table
 * in which enters data from the structure t_db_message
 * 
 * room: structure t_db_message with filled fields 
 * except room_id and date and status
 * 
 * return: complements the structure of t_db_message
 */
void mx_insert_message(sqlite3 *db, t_db_message *message) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    message->date = mx_get_time(DB_MILISECOND);
    message->status = DB_MSG_START;
    rv = sqlite3_prepare_v2(db, "insert into messages(user_id, room_id, date,"
                                "type, message, file_size, file_name, status,"
                                "power)values(?1, ?2, ?3, ?4, ?5, ?6, ?7,"
                                "?8, ?9)",
                            -1, &stmt, NULL);
    mx_error_sqlite(rv, "insert message");
    sqlite_bind_msg(stmt, message);
    mx_error_sqlite(sqlite3_step(stmt), "insert message");
    sqlite3_finalize(stmt);
    get_id_msg(db, message);
    mx_db_update_room_power(db, message->power, message->room_id);
}
