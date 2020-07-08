#include "server.h"

/*
 * Function: mx_is_members
 * -------------------------------
 * checks for a record of the connection of this 
 * user with this room
 * 
 * user_id: user id
 * room_id: room id
 * 
 * return: TRUE or FALSE
 */
gboolean mx_is_member(sqlite3 *db, guint64 user_id, guint64 room_id) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "select * from members where user_id = ?1 "
                                "and room_id = ?2", -1, &stmt, 0);
    mx_error_sqlite(rv, "is memebr");
    sqlite3_bind_int64(stmt, 1, user_id);
    sqlite3_bind_int64(stmt, 2, room_id);
    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return TRUE;
    }
    mx_error_sqlite(rv, "is memebr");
    sqlite3_finalize(stmt);
    return FALSE;
}

/*
 * Function: mx_get_login_members
 * -------------------------------
 * finds and writes in GList logins of users which are in the given room
 * and are not forbidden
 * 
 * room_id: room id
 * 
 * return: GList with login users
 */
GList *mx_get_login_members(sqlite3 *db, guint64 room_id) {
    sqlite3_stmt *stmt;
    gint rv = SQLITE_OK;
    GList *list = NULL;

    rv = sqlite3_prepare_v2(db, "select distinct login from users inner join "
                                "members on users.id = members.user_id where "
                                "room_id = ?1 and permission != ?2",
                            -1, &stmt, 0);
    mx_error_sqlite(rv, "get login members");
    sqlite3_bind_int64(stmt, 1, room_id);
    sqlite3_bind_int(stmt, 2, DB_BANNED);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        list = g_list_append(list, strdup((char*)sqlite3_column_text(stmt,
                             0)));
    mx_error_sqlite(rv, "get login members");
    sqlite3_finalize(stmt);
    return list;
}

/*
 * Function: 
 * 
 */
static cJSON *get_object_user(sqlite3_stmt *stmt) {
    cJSON *user = cJSON_CreateObject();

    cJSON_AddNumberToObject(user, "id", sqlite3_column_int64(stmt, 0));
    cJSON_AddStringToObject(user, "login", 
                            (char *)sqlite3_column_text(stmt, 1));
    cJSON_AddNumberToObject(user, "type", sqlite3_column_int(stmt, 2));
    return user;
}

/*
 * Function: mx_get_json_members
 * -------------------------------
 * retrieves from the database and enters in json an 
 * array of all user data that is in the room
 * 
 * room_id: room id
 * 
 * return: json object
 */

cJSON *mx_get_json_members(sqlite3 *db, guint64 room_id) {
    cJSON *users = cJSON_CreateArray();
    sqlite3_stmt *stmt;
    gint32 rv = 0;

    rv = sqlite3_prepare_v2(db, "select id, login, permission from users inner"
                                " join members on users.id = members.user_id "
                                "where room_id = ?1 and permission != ?2",
                            -1, &stmt, NULL);
    mx_error_sqlite(rv, "get json members");
    sqlite3_bind_int64(stmt, 1, room_id);
    sqlite3_bind_int(stmt, 2, DB_BANNED);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        cJSON_AddItemToArray(users, get_object_user(stmt));
    mx_error_sqlite(rv, "get json members");
    sqlite3_finalize(stmt);
    return users;
}

/*
 * Function: mx_get_type_member
 * -------------------------------
 * determines what rights this user has in this room
 * 
 * user_id: user id
 * room_id: room id
 * 
 * return permissiom user in this room
 */
gint8 mx_get_type_member(sqlite3 *db, guint64 user_id, guint64 room_id) {
    sqlite3_stmt *stmt;
    gint32 rv = 0;
    gint8 perm_user = -1;

    rv = sqlite3_prepare_v2(db, "select permission from members where "
                                "room_id = ?1 and user_id = ?2 ", 
                            -1, &stmt, NULL);
    mx_error_sqlite(rv, "get type member");
    sqlite3_bind_int64(stmt, 1, room_id);
    sqlite3_bind_int64(stmt, 2, user_id);
    if ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        perm_user = sqlite3_column_int(stmt, 0);
    mx_error_sqlite(rv, "get type member");
    sqlite3_finalize(stmt);
    return perm_user;
}

