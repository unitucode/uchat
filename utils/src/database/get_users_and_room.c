#include "utils.h"

static t_user *for_get_user(sqlite3_stmt *stmt) {
    t_user *user = NULL;
    int rv;
    
    if ((rv = sqlite3_step(stmt)) != SQLITE_ROW) {
        if (rv == SQLITE_ERROR)
            mx_elogger(MX_LOG_FILE, LOGERR, "get user");
        sqlite3_finalize(stmt);
        return NULL;
    }
    user = mx_malloc(sizeof(t_user));
    user->login = strdup((const char*)sqlite3_column_text(stmt, 0));
    user->password = strdup((const char*)sqlite3_column_text(stmt, 1));
    user->token = strdup((const char*)sqlite3_column_text(stmt, 2));
    user->permission = sqlite3_column_int(stmt, 3);
    user->on_off = sqlite3_column_int(stmt, 4);
    sqlite3_finalize(stmt);
    return user;
}

t_user *mx_get_user_by_login(sqlite3 *database, char *login) {
    sqlite3_stmt *stmt;
    int rv = 0;

    sqlite3_prepare_v3(database, "SELECT * FROM USERS WHERE login = ?1",
        -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    if (rv != SQLITE_OK)
        mx_elogger(MX_LOG_FILE, LOGERR, "get user");
    return for_get_user(stmt);
}

t_user *mx_get_user_by_token(sqlite3 *database, char *token) {
    sqlite3_stmt *stmt;
    int rv = 0;

    sqlite3_prepare_v3(database, "SELECT * FROM USERSS WHERE token = ?1",
        -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, token, -1, SQLITE_STATIC);
    if (rv != SQLITE_OK)
        mx_elogger(MX_LOG_FILE, LOGERR, "get user");
    return for_get_user(stmt);
}


t_room *mx_get_room(sqlite3 *database, char *name_room) {
    t_room *room = NULL;
    int rv;
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(database, "SELECT * FROM ROOMS WHERE name_room = ?1",
        -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
    if ((rv = sqlite3_step(stmt)) != SQLITE_ROW) {
        if (rv == SQLITE_ERROR)
            mx_elogger(MX_LOG_FILE, LOGERR, "get room");
        sqlite3_finalize(stmt);
        return NULL;
    }
    room = malloc(sizeof(t_room));
    room->id = sqlite3_column_int(stmt, 0);
    room->name_room = strdup((const char*)sqlite3_column_text(stmt, 1));
    room->customer = strdup((const char*)sqlite3_column_text(stmt, 2));
    sqlite3_finalize(stmt);
    return room;
}
