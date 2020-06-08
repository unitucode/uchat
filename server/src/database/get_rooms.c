#include "utils.h"

static cJSON *get_object_room(sqlite3_stmt *stmt) {
    cJSON *room = cJSON_CreateObject();

    cJSON_AddItemToObject(room, "id_room",
        cJSON_CreateNumber(sqlite3_column_int(stmt, 0)));
    cJSON_AddItemToObject(room, "name_room",
        cJSON_CreateString((char *)sqlite3_column_text(stmt, 1)));
    cJSON_AddItemToObject(room, "customer_login",
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
        "SELECT * FROM ROOMS WHERE DATE > ?1 ORDER BY DATE",
         -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, date);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        cJSON_AddItemToArray(rooms, get_object_room(stmt));
    sqlite3_finalize(stmt);
    return rooms;
}
