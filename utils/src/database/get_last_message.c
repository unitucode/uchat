#include "list.h"
#include "utils.h"

cJSON *mx_get_last_message(sqlite3 *database, 
                         char *name_room, long long date) {
    cJSON *room = cJSON_CreateObject();
    cJSON *message = cJSON_CreateArray();
    sqlite3_str *str = sqlite3_str_new(database);
    sqlite3_stmt *stmt;
    char *sql = NULL;
    int rv = 0;

    cJSON_AddItemToObject(room, "name_room", cJSON_CreateString(name_room));
    sqlite3_str_appendall(str, "SELECT * FROM ");
    sqlite3_str_appendall(str, name_room);
    sqlite3_str_appendall(str, " WHERE DATE > ");
    sqlite3_str_appendall(str, "?1");
    sqlite3_str_appendall(str, "ORDER BY DATE");
    sql = sqlite3_str_finish(str);
    rv = sqlite3_prepare_v3(database, sql, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, date);
    for (int i = 0; i < 30 && 
                    (rv = sqlite3_step(stmt)) == SQLITE_ROW; i++) {
        printf("%d\n", rv);
        cJSON_AddItemToArray(message, mx_get_object_message(stmt));
    }
    sqlite3_free(sql);
    sqlite3_finalize(stmt);
    cJSON_AddItemToObject(room, "message", message);
    return room;
}
