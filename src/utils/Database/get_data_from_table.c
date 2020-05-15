#include <utils.h>

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
    sqlite3_finalize(stmt);
    return user;
}

t_user *mx_get_user_by_login(char *login, sqlite3 *db_user) {
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db_user, "SELECT * FROM USERS WHERE login = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    return for_get_user(stmt);
}

t_user *mx_get_user_by_token(char *token, sqlite3 *db_user) {
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(db_user, "SELECT * FROM USERSS WHERE token = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, token, -1, SQLITE_STATIC);
    return for_get_user(stmt);
}


t_room *mx_get_room(char *name_room, sqlite3 *database) {
    t_room *room = malloc(sizeof(t_room));
    int returnvalue;
    sqlite3_stmt *stmt;

    sqlite3_prepare_v3(database, "SELECT * FROM ROOMS WHERE room_name = ?1", -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
    if ((returnvalue = sqlite3_step(stmt)) != SQLITE_ROW) {
        printf("error get room");
        sqlite3_finalize(stmt);
        // mx_free((void**)room);
        return NULL;
    }
    room->id = sqlite3_column_int(stmt, 0);
    room->name = strdup((const char*)sqlite3_column_text(stmt, 1));
    room->customer = strdup((const char*)sqlite3_column_text(stmt, 2));
    sqlite3_finalize(stmt);
    return room;
}

// t_members_room *mx_get_members_room(int id_room, sqlite3 *database) {
//     t_members_room *members_room = malloc(sizeof(t_members_room));
//     int returnvalue;
//     sqlite3_stmt *stmt;

//     sqlite3_prepare_v3(database, "SELECT MEMBER_LOGIN FROM MEMBER WHERE id_room = ?1", -1, 0, &stmt, NULL);
//     sqlite3_bind_text(stmt, 1, id_room, -1, SQLITE_STATIC);
//     while (sqlite3_step(stmt) == SQLITE_ROW) {
//         if (members_room->login == NULL) {

//         }
//             members_room->login = strdup(sqlite3_column_text(stmt, 0));
//         else {

//         }
//     }
//     if ((returnvalue = sqlite3_step(stmt)) != SQLITE_ROW) {
//         printf("error get room");
//         // mx_free((void**)room);
//         return NULL;
//     }
//     return members_room;
// }
