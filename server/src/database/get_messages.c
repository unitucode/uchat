#include "server.h"

/*request func flag:
* 0 -> curr_message
* 1 -> new_message
* 2 -> old_message
*/
static cJSON *get_object_message(sqlite3_stmt *stmt) {
    cJSON *object_message = cJSON_CreateObject();

    cJSON_AddItemToObject(object_message, "id_message",
        cJSON_CreateNumber(sqlite3_column_int(stmt, 0)));
    cJSON_AddItemToObject(object_message, "login",
        cJSON_CreateString((char *)sqlite3_column_text(stmt, 1)));
    cJSON_AddItemToObject(object_message, "date",
        cJSON_CreateNumber(sqlite3_column_int(stmt, 2)));
    cJSON_AddItemToObject(object_message, "msg",
        cJSON_CreateString((char *)sqlite3_column_text(stmt, 3)));
    return object_message;
}

static cJSON *get_messages(sqlite3_stmt *stmt, char *name_room, int count,
                       long int date) {
    cJSON *room = cJSON_CreateObject();
    cJSON *message = cJSON_CreateArray();
    int rv = 0;

    sqlite3_bind_int(stmt, 1, date);
    for (int i = 0; i < count 
                        && (rv = sqlite3_step(stmt)) == SQLITE_ROW; i++) {
        cJSON_AddItemToArray(message, get_object_message(stmt));
    }
    cJSON_AddItemToObject(room, "name_room", cJSON_CreateString(name_room));
    cJSON_AddItemToObject(room, "messages", message);
    sqlite3_finalize(stmt);
    return room;
}

cJSON *mx_get_new_messages(sqlite3 *database, char *name_room,
                           long int date, int count) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;
    char *request = mx_create_request_message(database, name_room, 1);

    rv = sqlite3_prepare_v3(database, request, -1, 0, &stmt, NULL);
    sqlite3_free(request);
    return get_messages(stmt, name_room, count, date);
}

cJSON *mx_get_curr_messages(sqlite3 *database, char *name_room, int count) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;
    char *request = mx_create_request_message(database, name_room, 0);

    rv = sqlite3_prepare_v3(database, request, -1, 0, &stmt, NULL);
    sqlite3_free(request);
    return get_messages(stmt, name_room, count, 0);
}

cJSON *mx_get_old_messages(sqlite3 *database, char *name_room,
                           long int date, int count) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;
    char *request = mx_create_request_message(database, name_room, 2);
    
    rv = sqlite3_prepare_v3(database, request, -1, 0, &stmt, NULL);
    sqlite3_free(request);
    return get_messages(stmt, name_room, count, date);
}


