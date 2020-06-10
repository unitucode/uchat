#include "server.h"

static cJSON *get_object_room(sqlite3_stmt *stmt) {
    cJSON *room = cJSON_CreateObject();

    cJSON_AddItemToObject(room, "id",
        cJSON_CreateNumber(sqlite3_column_int(stmt, 0)));
    cJSON_AddItemToObject(room, "room_name",
        cJSON_CreateString((char *)sqlite3_column_text(stmt, 1)));
    cJSON_AddItemToObject(room, "customer",
        cJSON_CreateString((char *)sqlite3_column_text(stmt, 2)));
    cJSON_AddItemToObject(room, "date",
        cJSON_CreateNumber(sqlite3_column_int(stmt, 3)));
    return room;
}

cJSON *mx_get_rooms(sqlite3 *database, long int date) {
    cJSON *rooms = cJSON_CreateArray();
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(database, 
        "SELECT * FROM ROOMS WHERE DATE > ?1 ORDER BY DATE DESC",
         -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, date);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        cJSON_AddItemToArray(rooms, get_object_room(stmt));
    sqlite3_finalize(stmt);
    return rooms;
}

bool mx_is_exists_room_by_id(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
    int rv = 1;
    char *request = NULL; 

    sqlite3_str_appendall(str, "select name from sqlite_master where type "
                                "= 'table' and name = ");
    sqlite3_str_appendf(str, "room%d", id);
    request = sqlite3_str_finish(str);
    mx_error_sqlite(sqlite3_prepare_v2(db, request, -1, &stmt, NULL), "prepar",
                                       "delete room by id");
    mx_error_sqlite(sqlite3_step(stmt), "step", "delete room by id");
    if (!sqlite3_column_text(stmt, 0))
        rv = 0;
    sqlite3_finalize(stmt);
    return rv;
}
