#include "server.h"

/*
 * Function:
 * -------------------------------
 * 
 */
static t_db_user *for_get_user(sqlite3_stmt *stmt) {
    t_db_user *user = NULL;

    if (sqlite3_step(stmt) == 100) {
        user = mx_malloc(sizeof(t_db_user));
        user->user_id = sqlite3_column_int64(stmt, 0);
        user->name = strdup((const char *)sqlite3_column_text(stmt, 1));
        user->login = strdup((const char*)sqlite3_column_text(stmt, 2));
        user->pass = strdup((const char*)sqlite3_column_text(stmt, 3));
        user->token = strdup((const char*)sqlite3_column_text(stmt, 4));
        user->date = sqlite3_column_int(stmt, 5);
        user->desc = strdup(MX_J_STR((char*)sqlite3_column_text(stmt, 6)));
    }
    sqlite3_finalize(stmt);
    return user;
}

/*
 * Function: mx_get_user_by_login
 * -------------------------------
 * get data of user in t_db_user
 * 
 * login: login of user
 * 
 * return: struct t_db_room with data of user
 */
t_db_user *mx_get_user_by_login(sqlite3 *db, gchar *login) {
    sqlite3_stmt *stmt;
    gint32 rv = 0;

    rv = sqlite3_prepare_v3(db, "select * from users where login = ?1",
                            -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    mx_error_sqlite(rv, "get user by login");
    return for_get_user(stmt);
}

/*
 * Function: mx_get_user_by_id
 * -------------------------------
 * get data of user in t_db_user
 * 
 * user_id: user id
 * 
 * return: struct t_db_room with data of user
 */
t_db_user *mx_get_user_by_id(sqlite3 *db, guint64 user_id) {
    sqlite3_stmt *stmt;
    gint32 rv = 0;

    rv = sqlite3_prepare_v3(db, "select * from users where id = ?1",
                            -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "get user by id");
    sqlite3_bind_int64(stmt, 1, user_id);
    return for_get_user(stmt);
}

/*
 * Function: mx_get_user_by_token
 * -------------------------------
 * get data of user in t_db_user
 * 
 * token: token of user
 * 
 * return: struct t_db_room with data of user
 */
t_db_user *mx_get_user_by_token(sqlite3 *db, gchar *token) {
    sqlite3_stmt *stmt;
    gint32 rv = 0;

    rv = sqlite3_prepare_v3(db, "select * from users where token = ?1",
                            -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "get user by token");
    sqlite3_bind_text(stmt, 1, token, -1, SQLITE_STATIC);
    return for_get_user(stmt);
}

/*
 * Function: mx_get_room_by_id
 * -------------------------------
 * get data of room in t_db_room
 * 
 * id: room id
 * 
 * return: struct t_db_room with data of room
 */

t_db_room *mx_get_room_by_id(sqlite3 *db, guint64 id) {
    t_db_room *room = NULL;
    sqlite3_stmt *stmt;

    mx_error_sqlite(sqlite3_prepare_v3(db, "select * from rooms where "
                                           "id = ?1",
                                       -1, 0, &stmt, NULL), "get room by id");
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) == 100) {
        room = malloc(sizeof(t_db_room));
        room->room_id = sqlite3_column_int64(stmt, 0);
        room->room_name = strdup((const char*)sqlite3_column_text(stmt, 1));
        room->customer_id = sqlite3_column_int64(stmt, 2);
        room->date = sqlite3_column_int64(stmt, 3);
        room->desc = strdup(MX_J_STR((char*)sqlite3_column_text(stmt, 4)));
        room->type = sqlite3_column_int(stmt, 5);
        room->power = sqlite3_column_int64(stmt, 6);
    }
    sqlite3_finalize(stmt);
    return room;
}

