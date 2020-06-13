#include "server.h"

void mx_edit_message(sqlite3 *db, unsigned long long id_room,
                     unsigned long long id, char *new) {
    sqlite3_str *str = sqlite3_str_new(db);
    sqlite3_stmt *stmt;
    char *request = NULL;

    sqlite3_str_appendf(str, "update room%llu set message = ?1 where "
                             "id_message = %llu", id_room, id);
    request = sqlite3_str_finish(str);
    mx_error_sqlite(sqlite3_prepare(db, request, -1, &stmt, NULL), "prepare",
                    "edit message");
    sqlite3_bind_text(stmt, 1, new, -1, SQLITE_STATIC);
    mx_error_sqlite(sqlite3_step(stmt), "step", "edit message");
    sqlite3_free(request);
    sqlite3_finalize(stmt);
}
