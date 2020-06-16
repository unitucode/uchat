#include "server.h"

static t_db_user *for_get_user(sqlite3_stmt *stmt) {
    if (sqlite3_step(stmt) == 100) {
        t_db_user *user = mx_malloc(sizeof(t_db_user));
        user->login = strdup((const char*)sqlite3_column_text(stmt, 0));
        user->password = strdup((const char*)sqlite3_column_text(stmt, 1));
        user->token = strdup((const char*)sqlite3_column_text(stmt, 2));
        user->permission = sqlite3_column_int(stmt, 3);
        user->date = sqlite3_column_int(stmt, 4);
        user->description = strdup((const char *)sqlite3_column_text(stmt, 5));
        sqlite3_finalize(stmt);
        return user;
    }
    sqlite3_finalize(stmt);
    return NULL;
}

t_db_user *mx_get_user_by_login(sqlite3 *database, char *login) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(database, "select * from users where login = ?1",
        -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    mx_error_sqlite(rv, "prepare", "get_user_by_login");
    return for_get_user(stmt);
}

t_db_user *mx_get_user_by_token(sqlite3 *database, char *token) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(database, "select * from users where token = ?1",
        -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "get user by token");
    sqlite3_bind_text(stmt, 1, token, -1, SQLITE_STATIC);
    return for_get_user(stmt);
}

t_db_room *mx_get_room_by_id(sqlite3 *database, unsigned long long int id) {
    t_db_room *room = NULL;
    sqlite3_stmt *stmt;

    mx_error_sqlite(sqlite3_prepare_v3(database, "select * from rooms where "
        "id = ?1", -1, 0, &stmt, NULL), "prepare", "get_room");
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) == 100) {
        room = malloc(sizeof(t_db_room));
        room->id = sqlite3_column_int(stmt, 0);
        room->room_name = strdup((const char*)sqlite3_column_text(stmt, 1));
        room->customer = strdup((const char*)sqlite3_column_text(stmt, 2));
        room->date = sqlite3_column_int(stmt, 3);
        room->description = strdup((const char*)sqlite3_column_text(stmt, 4));
    }
    sqlite3_finalize(stmt);
    return room;
}

// to delete
t_db_room *mx_get_room(sqlite3 *database, char *name_room) {
    t_db_room *room = NULL;
    sqlite3_stmt *stmt;

    mx_error_sqlite(sqlite3_prepare_v3(database, "select * from rooms where "
                                                 "name = ?1 order by date desc",
                                       -1, 0, &stmt, NULL),
                                       "prepare", "get_room");
    sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == 100) {
        room = malloc(sizeof(t_db_room));
        room->id = sqlite3_column_int(stmt, 0);
        room->room_name = strdup((const char*)sqlite3_column_text(stmt, 1));
        room->customer = strdup((const char*)sqlite3_column_text(stmt, 2));
        room->date = sqlite3_column_int64(stmt, 3);
        room->description = mx_strdup((char*)sqlite3_column_text(stmt, 4));
    }
    sqlite3_finalize(stmt);
    return room;
}
