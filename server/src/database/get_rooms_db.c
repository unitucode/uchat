#include "server.h"

/*
 * Function: mx_get_object_room
 * -------------------------------
 * creates an json object with room data
 * 
 * stmt: sqlite request
 * 
 * return: json object
 */
cJSON *mx_get_object_room(sqlite3_stmt *stmt) {
    cJSON *room = cJSON_CreateObject();

    cJSON_AddNumberToObject(room, "id", sqlite3_column_int64(stmt, 0));
    cJSON_AddStringToObject(room, "name", 
                            MX_J_STR((char*)sqlite3_column_text(stmt, 1)));
    cJSON_AddNumberToObject(room, "customer_id", 
                            sqlite3_column_int64(stmt, 2));
    cJSON_AddNumberToObject(room, "date", sqlite3_column_int64(stmt, 3));
    cJSON_AddStringToObject(room, "desc", 
                            MX_J_STR((char*)sqlite3_column_text(stmt, 4)));
    cJSON_AddNumberToObject(room, "type", sqlite3_column_int(stmt, 5));
    cJSON_AddNumberToObject(room, "power", sqlite3_column_int64(stmt, 6));
    return room;
}

/*
 * Function: mx_get_rooms
 * -------------------------------
 * returns all user rooms where he can be active
 * rooms that have been created so far are not taken into account
 * 
 * date: time in milisecond
 * user_id: user id
 * 
 * return: json object
 */
cJSON *mx_get_rooms(sqlite3 *db, guint64 date, guint64 user_id) {
    cJSON *rooms = cJSON_CreateArray();
    sqlite3_stmt *stmt;
    gint32 rv = 0;

    rv = sqlite3_prepare_v2(db, "select * from rooms where id in (select room"
                                "_id from members where user_id = ?2 and "
                                "permission != ?3) and date > ?1 order by "
                                "date desc",
                            -1, &stmt, NULL);
    mx_error_sqlite(rv, "get rooms");
    sqlite3_bind_int64(stmt, 1, date);
    sqlite3_bind_int64(stmt, 2, user_id);
    sqlite3_bind_int(stmt, 3, DB_BANNED);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        cJSON_AddItemToArray(rooms, mx_get_object_room(stmt));
    mx_error_sqlite(rv, "get rooms");
    sqlite3_finalize(stmt);
    return rooms;
}
