#include "utils.h"

static cJSON *get_object_room(sqlite3_stmt *stmt) {
    cJSON *room = cJSON_CreateObject();

    cJSON_AddItemToObject(room, "id_room",
        cJSON_CreateNumber(sqlite3_column_int(stmt, 0)));
    cJSON_AddItemToObject(room, "name_room",
        cJSON_CreateString((char *)sqlite3_column_text(stmt, 1)));
    cJSON_AddItemToObject(room, "customer_login",
        cJSON_CreateString((char*)sqlite3_column_text(stmt, 2)));
    cJSON_AddItemToObject(room, "date",
        cJSON_CreateNumber(sqlite3_column_int(stmt, 3)));
    return room;
}

cJSON *mx_get_room_all(sqlite3 *database) {
    cJSON *room = cJSON_CreateObject();
    cJSON *rooms = cJSON_CreateArray();
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(database, "SELECT * FROM ROOMS", -1, 0, &stmt, NULL);
    while ((rv = sqlite3_step(stmt)) == SQLITE_ROW)
        cJSON_AddItemToArray(rooms, get_object_room(stmt));
    cJSON_AddItemToObject(room, "rooms", rooms);
    sqlite3_finalize(stmt);
    return room;
}

// mx_get_room_by_data(long int data) {

// }


// static cJSON *get_json(sqlite3 *database, t_id_room *id) {
//     cJSON *object = cJSON_CreateObject();
//     cJSON *rooms = cJSON_CreateArray();
//     sqlite3_stmt *stmt;
//     int rv;

//     while (id != NULL) {
//         rv = sqlite3_prepare_v3(database, "SELECT * FROM ROOMS WHERE id = ?1",
//             -1, 0, &stmt, NULL);
//         sqlite3_bind_int(stmt, 1, id->id_room);
//         rv = sqlite3_step(stmt);
//         if (rv == SQLITE_ROW)
//             cJSON_AddItemToArray(rooms, get_data_room(database, stmt));
//         id = id->next;
//     }
//     cJSON_AddItemToObject(object, "rooms", rooms);
//     sqlite3_finalize(stmt);
//     return object;
// }

