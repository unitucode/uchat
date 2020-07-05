#include "server.h"

/*
 * Function: mx_search_user
 * -------------------------------
 * finds and writes to json an array of usernames 
 * whose name begins with str_search
 * 
 * str_search: the name of the user they are looking for
 * 
 * return: json object
 */
cJSON *mx_search_user(sqlite3 *db, gchar *str_search) {
    sqlite3_str *sql_str = sqlite3_str_new(db);
    gint32 rv =SQLITE_OK;
    gchar *request = NULL;
    sqlite3_stmt *stmt;
    cJSON *users = cJSON_CreateArray();

    sqlite3_str_appendf(sql_str, "select * from users where name like '%s%%'", 
                        str_search);
    request = sqlite3_str_finish(sql_str);
    mx_error_sqlite(sqlite3_prepare_v2(db, request, -1, &stmt, 0),
                    "db search user");
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        cJSON_AddItemToArray(users, mx_get_object_user(stmt));
    mx_error_sqlite(rv, "db search room");
    sqlite3_free(request);
    sqlite3_finalize(stmt);
    return users;
}

/*
 * Function: mx_search_room
 * -------------------------------
 * finds and writes to json an array of room names whose name begins with 
 * str_search and to which this user belongs
 * 
 * str_search: the name of the room they are looking for
 * user_id: user id
 * 
 * return: json object
 */
cJSON *mx_search_room(sqlite3 *db, gchar *str_search, guint64 user_id) {
    sqlite3_str *sql_str = sqlite3_str_new(db);
    gint32 rv = SQLITE_OK;
    gchar *request = NULL;
    sqlite3_stmt *stmt;
    cJSON *rooms = cJSON_CreateArray();

    sqlite3_str_appendf(sql_str, "select * from rooms where name like '%s%%' "
                                 "and id not in(select room_id from membe"
                                 "rs where user_id = %llu)",
                        str_search, user_id);
    request = sqlite3_str_finish(sql_str);
    mx_error_sqlite(sqlite3_prepare_v2(db, request, -1, &stmt, NULL),
                    "db search room");
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        cJSON_AddItemToArray(rooms, mx_get_object_room(stmt));
    mx_error_sqlite(rv, "db search room");
    sqlite3_free(request);
    sqlite3_finalize(stmt);
    return rooms;
}

/*
 * Function: mx_check_user_by_login
 * -------------------------------
 * checks if the user exists by his login
 * 
 * login: login user
 * 
 * return: TRUE if the user exists
 */
gboolean mx_check_user_by_login(sqlite3 *db, gchar *login) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "select * from users where login = ?1",
                       -1, &stmt, 0);
    mx_error_sqlite(rv, "mx_check_user_by_login");
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return TRUE;
    }
    mx_error_sqlite(rv, "mx_check_user_by_login");
    sqlite3_finalize(stmt);
    return FALSE;
}

/*
 * Function: mx_search_message
 * -------------------------------
 * searches writes to json and returns 
 * only text messages that start on str_search
 * 
 * str_search: test to find
 * room_id: room id
 * 
 * return: json object
 */
cJSON *mx_search_message(sqlite3 *db, gchar *str_search, guint64 room_id) {
    sqlite3_str *sql_str = sqlite3_str_new(db);
    gint32 rv = SQLITE_OK;
    gchar *request = NULL;
    sqlite3_stmt *stmt;
    cJSON *messages = cJSON_CreateArray();

    sqlite3_str_appendf(sql_str, "select * from messages where room_id = %llu"
                                 " and message like '%%%s%%' and type = %d",
                        room_id, str_search, DB_TEXT_MSG);
    request = sqlite3_str_finish(sql_str);
    mx_error_sqlite(sqlite3_prepare_v2(db, request, -1, &stmt, NULL), 
                    "db search message");
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        cJSON_AddItemToArray(messages, mx_get_object_message(stmt));
    mx_error_sqlite(rv, "db search message");
    sqlite3_free(request);
    sqlite3_finalize(stmt);
    return messages;
}
