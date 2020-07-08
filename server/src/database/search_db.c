#include "server.h"

static gchar *parse_str_search(gchar *str) {
    gchar *tmp = NULL;
    gint size = (gint)strlen(str);
    gint tmp_point = 0;

    for (gint i = 0; i < (gint)strlen(str); i++) {
        if (str[i] == '%' || str[i] == '_' || str[i] == '\\')
            size++;
    }
    tmp = malloc(size + 1);
    tmp[size] = 0;
    for (gint i = 0; i < (gint)strlen(str); i++, tmp_point++) {
        if (str[i] == '%' || str[i] == '_' || str[i] == '\\') {
            tmp[tmp_point++] = '\\';
            tmp[tmp_point] = str[i];
        }
        else
            tmp[tmp_point] = str[i];
    }
    return tmp;
}

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
    gint32 rv = SQLITE_OK;
    sqlite3_stmt *stmt;
    gchar *str_search_join = NULL;
    cJSON *users = cJSON_CreateArray();
    str_search = parse_str_search(str_search);

    str_search_join = g_strjoin("", "%%", str_search, "%%", NULL);
    sqlite3_prepare_v2(db, "select * from users where name like ?1 "
                           "escape '\\'",
                       -1, &stmt, 0),
    sqlite3_bind_text(stmt, 1, str_search_join, -1, SQLITE_STATIC);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        cJSON_AddItemToArray(users, mx_get_object_user(stmt));
    mx_error_sqlite(rv, "db search room");
    g_free(str_search_join);
    mx_free((void **)&str_search);
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
    gint32 rv = SQLITE_OK;
    sqlite3_stmt *stmt;
    gchar *str_search_join = NULL;
    cJSON *rooms = cJSON_CreateArray();

    str_search = parse_str_search(str_search);
    str_search_join = g_strjoin("", str_search, "%%", NULL);
    rv = sqlite3_prepare_v2(db, "select * from rooms where name like ?1 escape"
                                " '\\' and id not in(select room_id from membe"
                                "rs where user_id = ?2)",
                            -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, str_search_join, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 2, user_id);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        cJSON_AddItemToArray(rooms, mx_get_object_room(stmt));
    mx_error_sqlite(rv, "db search room");
    g_free(str_search_join);
    mx_free((void **)&str_search);
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
    gint32 rv = SQLITE_OK;
    gchar *str_search_join = NULL;
    sqlite3_stmt *stmt;
    cJSON *messages = cJSON_CreateArray();

    str_search = parse_str_search(str_search);
    str_search_join = g_strjoin("", "%%", str_search, "%%", NULL);
    sqlite3_prepare_v2(db, "select * from messages where room_id = ?2"
                           " and message like ?1 escape '\\' and type = ?3",
                       -1, &stmt, NULL),
    sqlite3_bind_text(stmt, 1, str_search_join, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 2, room_id);
    sqlite3_bind_int(stmt, 3, DB_TEXT_MSG);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        cJSON_AddItemToArray(messages, mx_get_object_message(stmt));
    mx_error_sqlite(rv, "db search message");
    sqlite3_free(str_search_join);
    mx_free((void**)&str_search);
    sqlite3_finalize(stmt);
    return messages;
}
