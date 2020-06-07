#include "list.h"
#include "utils.h"

static char *create_request(sqlite3 *database, char *name_room) {
    sqlite3_str *str = sqlite3_str_new(database);
    char *request = NULL;

    sqlite3_str_appendall(str, "SELECT * FROM ");
    sqlite3_str_appendall(str, name_room);
    sqlite3_str_appendall(str, " WHERE DATE < ");
    sqlite3_str_appendall(str, "?1");
    sqlite3_str_appendall(str, "ORDER BY DATE");
    request = sqlite3_str_finish(str);
    return request;
}

cJSON *mx_get_last_message(sqlite3 *database, 
                         char *name_room, long int date, int count) {
    cJSON *room = cJSON_CreateObject();
    cJSON *message = cJSON_CreateArray();
    sqlite3_stmt *stmt;
    int rv = 0;
    char *request = create_request(database, name_room);

    cJSON_AddItemToObject(room, "name_room", cJSON_CreateString(name_room));
    rv = sqlite3_prepare_v3(database, request, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, date);
    for (int i = 0; i < count && 
                    (rv = sqlite3_step(stmt)) == SQLITE_ROW; i++) {
        cJSON_AddItemToArray(message, mx_get_object_message(stmt));
    }
    if (rv != SQLITE_ROW && rv != SQLITE_DONE)
        mx_elogger(MX_LOG_FILE, LOGERR, "get_last_message");
    sqlite3_free(request);
    sqlite3_finalize(stmt);
    cJSON_AddItemToObject(room, "message", message);
    return room;
}
