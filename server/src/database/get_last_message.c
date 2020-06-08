#include "server.h"

t_db_message *mx_get_last_message(sqlite3 *database, char *name_room) {
    t_db_message *message = malloc(sizeof(t_db_message));
    sqlite3_stmt *stmt;
    char *request = NULL;
    int rv = 0;
    sqlite3_str *str = sqlite3_str_new(database);

    sqlite3_str_appendall(str, "SELECT * FROM '");
    sqlite3_str_appendall(str, name_room);
    sqlite3_str_appendall(str, "' ORDER BY DATE DESC");
    request = sqlite3_str_finish(str);
    rv = sqlite3_prepare_v3(database, request, -1, 0, &stmt, NULL);
    if (rv == SQLITE_ERROR)
        mx_logger(MX_LOG_FILE, LOGWAR, "get message with database prepa");
    if ((rv = sqlite3_step(stmt)) != SQLITE_DONE)
        mx_logger(MX_LOG_FILE, LOGWAR, "get message with database step");
    message->id_message = sqlite3_column_int(stmt, 0);
    message->login = strdup((char *)sqlite3_column_text(stmt, 1));
    message->date = sqlite3_column_int(stmt, 2);
    message->message = strdup((char *)sqlite3_column_text(stmt, 3));
    message->name_room = strdup(name_room);
    sqlite3_free(request);
    sqlite3_finalize(stmt);
    return message;
}
