#include "server.h"

cJSON *mx_search_user(sqlite3 *db, gchar *str_search) {
    sqlite3_str *sql_str = sqlite3_str_new(db);
    gint32 rv =SQLITE_OK;
    gchar *request = NULL;
    sqlite3_stmt *stmt;
    cJSON *users = cJSON_CreateArray();

    sqlite3_str_appendf(sql_str, "select * from users where name like '%s%%'", 
                        str_search);
    request = sqlite3_str_finish(sql_str);
    mx_error_sqlite(sqlite3_prepare_v2(db, request, -1, &stmt, 0), "prepare", "search user");
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        cJSON_AddItemToArray(users, mx_get_object_user(stmt));
    sqlite3_free(request);
    sqlite3_finalize(stmt);
    return users;
}

cJSON *mx_search_room(sqlite3 *db, gchar *str_search) {
    sqlite3_str *sql_str = sqlite3_str_new(db);
    gint32 rv = SQLITE_OK;
    gchar *request = NULL;
    sqlite3_stmt *stmt;
    cJSON *rooms = cJSON_CreateArray();

    sqlite3_str_appendf(sql_str, "select * from rooms where name like '%s%%'",
                        str_search);
    request = sqlite3_str_finish(sql_str);
    mx_error_sqlite(sqlite3_prepare_v2(db, request, -1, &stmt, 0), "prepare", "search room");
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        cJSON_AddItemToArray(rooms, mx_get_object_room(stmt));
    sqlite3_free(request);
    sqlite3_finalize(stmt);
    return rooms;
}

gboolean mx_check_user_by_login(sqlite3 *db, gchar *login) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    sqlite3_prepare_v2(db, "select * from users where login = ?1",
                       -1, &stmt, 0);
    rv = mx_error_sqlite(rv, "prepare", "check_user");
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return true;
    }
    mx_error_sqlite(rv, "step", "check_user");
    sqlite3_finalize(stmt);
    return false;
}