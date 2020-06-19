#include "server.h"

unsigned long long int mx_get_roomid_by_name(sqlite3 *db, char *name) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;
    unsigned long long int id = 0;

    rv = sqlite3_prepare_v2(db, "select id from rooms where name = ?1 order by date desc",
                            -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    mx_error_sqlite(rv, "prepare", "mx_get_room_id");
    mx_error_sqlite(sqlite3_step(stmt), "step", "mx_get_room_id");
    id = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return id;
}

static char *create_request(sqlite3 *database, unsigned long long int id) {
    sqlite3_str *str = sqlite3_str_new(database);

    sqlite3_str_appendall(str, "select * from ");
    sqlite3_str_appendf(str, "room%d ", id);
    sqlite3_str_appendall(str, "where login = ?1 order by id_message desc");
    return sqlite3_str_finish(str);
}

t_db_message *mx_get_last_message(sqlite3 *database, 
                                  unsigned long long int id, char *login) {
    t_db_message *message = malloc(sizeof(t_db_message));
    sqlite3_stmt *stmt;
    char *request = NULL;
    int rv = 0;

    request = create_request(database, id);
    rv = sqlite3_prepare_v3(database, request, -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "get last message");
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    mx_error_sqlite(sqlite3_step(stmt), "step", "get last message");
    message->id = sqlite3_column_int(stmt, 0);
    message->login = strdup((char *)sqlite3_column_text(stmt, 1));
    message->date = sqlite3_column_int(stmt, 2);
    message->message = strdup((char *)sqlite3_column_text(stmt, 3));
    message->room_id = id;
    sqlite3_free(request);
    sqlite3_finalize(stmt);
    return message;
}
