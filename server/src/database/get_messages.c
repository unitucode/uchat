#include "utils.h"

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
    cJSON_AddItemToObject(object_message, "message",
        cJSON_CreateString((char *)sqlite3_column_text(stmt, 3)));
    return object_message;
}

cJSON *mx_get_messages(t_gmp *pr) {
    cJSON *room = cJSON_CreateObject();
    cJSON *message = cJSON_CreateArray();
    sqlite3_stmt *stmt;
    char *request = mx_create_request_message(pr);
    int rv = 0;

    rv = sqlite3_prepare_v3(pr->db, request, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, pr->date);
    for (int i = 0; i < pr->count 
                        && (rv = sqlite3_step(stmt)) == SQLITE_ROW; i++) {
        cJSON_AddItemToArray(message, get_object_message(stmt));
    }
    cJSON_AddItemToObject(room, "name_room", cJSON_CreateString(pr->name_room));
    cJSON_AddItemToObject(room, "message", message);
    sqlite3_free(request);
    sqlite3_finalize(stmt);
    return room;
}
