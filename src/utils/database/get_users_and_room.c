#include "utils.h"

static t_user *for_get_user(sqlite3_stmt *stmt) {
    t_user *user = mx_malloc(sizeof(t_user));
    int returnvalue;
    
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_ROW) {
        printf("error get user");
        // mx_free((void**)user);
        return NULL;
    }
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

    sqlite3_prepare_v3(database, "SELECT * FROM USERS WHERE login = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    return for_get_user(stmt);
}

t_user *mx_get_user_by_token(sqlite3 *database, char *token) {
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(database, "SELECT * FROM USERSS WHERE token = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, token, -1, SQLITE_STATIC);
    return for_get_user(stmt);
}


t_rooms *mx_get_room(sqlite3 *database, char *name_room) {
    t_rooms *room = NULL;
    int returnvalue;
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(database, "SELECT * FROM ROOMS WHERE name_room = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_ROW) {
        printf("error get room\n");
        sqlite3_finalize(stmt);
        // mx_free((void**)room);
        return NULL;
    }
    room = malloc(sizeof(t_rooms));
    room->id = sqlite3_column_int(stmt, 0);
    room->name = strdup((const char*)sqlite3_column_text(stmt, 1));
    room->customer = strdup((const char*)sqlite3_column_text(stmt, 2));
    sqlite3_finalize(stmt);
    return room;
}
