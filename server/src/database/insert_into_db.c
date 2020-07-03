#include "server.h"

/*
 * Function: mx_insert_room_into_db
 * -------------------------------
 * makes an entry in the database in the rooms table
 * in which enters data from the structure t_db_room
 * 
 * room: structure t_db_room with filled fields except room_id and date
 * 
 * return: complements the structure of t_db_room
 */

static void sqlite_bind_room(sqlite3_stmt *stmt, t_db_room *room) {
    sqlite3_bind_text(stmt, 1, room->room_name, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 2, room->customer_id);
    sqlite3_bind_int64(stmt, 3, room->date);
    sqlite3_bind_text(stmt, 4, room->desc, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, room->type);
    sqlite3_bind_int64(stmt, 6, room->power);
}


void mx_insert_room_into_db(sqlite3 *db, t_db_room *room) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    room->date = mx_get_time(DB_MILISECOND);
    rv = sqlite3_prepare_v2(db, "insert into rooms(name, customer_id, date,"
                                " desc, type, power)values(?1, ?2, ?3, ?4, "
                                "?5, ?6);",
                            -1, &stmt, 0);
    mx_error_sqlite(rv);
    sqlite_bind_room(stmt, room);
    mx_error_sqlite(sqlite3_step(stmt));
    sqlite3_finalize(stmt);
    sqlite3_prepare_v2(db, "select max(id) from rooms", -1, &stmt, NULL);
    mx_error_sqlite(sqlite3_step(stmt));
    room->room_id = sqlite3_column_int64(stmt, 0);
    mx_insert_member_into_db(db, room->room_id, room->customer_id,
                             DB_CUSTOMER);
    sqlite3_finalize(stmt);
}

static void get_id_user(sqlite3 *db, t_db_user *user) {
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(db, "select max(id) from users", -1, &stmt, NULL);
    mx_error_sqlite(sqlite3_step(stmt));
    user->user_id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
}

/*
 * Function: mx_insert_user_into_db
 * -------------------------------
 * makes an entry in the database in the users table
 * in which enters data from the structure t_db_user
 * 
 * room: structure t_db_user with filled fields except user_id and date
 * 
 * return: complements the structure of t_db_user
 */

void mx_insert_user_into_db(sqlite3 *db, t_db_user *user) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    user->date = mx_get_time(DB_MILISECOND);
    rv = sqlite3_prepare_v2(db, "insert into users(name, login, pass, token, "
                                "date, desc)values(?1, ?2, ?3, ?4, ?5, ?6);",
                            -1, &stmt, NULL);
    mx_error_sqlite(rv);
    sqlite3_bind_text(stmt, 1, user->name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user->login, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, user->pass, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, user->token, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 5, user->date);
    sqlite3_bind_text(stmt, 6, user->desc, -1, SQLITE_STATIC);
    mx_error_sqlite(sqlite3_step(stmt));
    sqlite3_finalize(stmt);
    get_id_user(db, user);
}

/*
 * Function: mx_insert_member_into_db
 * -------------------------------
 * makes an entry in the database in the members table
 * 
 * room_id: room id
 * user_id: user id
 * permission: user rights in this room
 */

void mx_insert_member_into_db(sqlite3 *db, guint64 room_id, guint64 user_id,
                              gint8 permission) {
    gint32 rv = SQLITE_OK;
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gchar *request = NULL;

    sqlite3_str_appendf(sqlite_str, "insert into members(user_id, room_id,"
                                    " date, permission)values(%lu, %lu, "
                                    "%llu, %d);",
                        user_id, room_id, mx_get_time(DB_MILISECOND),
                        permission);
    request = sqlite3_str_finish(sqlite_str);
    rv = sqlite3_exec(db, request, 0, 0, 0);
    mx_error_sqlite(rv);
    sqlite3_free(request);
}
