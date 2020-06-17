#include "server.h"


void mx_delete_message_by_id(sqlite3 *db, guint64 id) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "delete from messages where message_id "
                                "= ?1", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    mx_error_sqlite(rv, "prepare", "delete message");
    mx_error_sqlite(sqlite3_step(stmt), "step", "delete message");
    sqlite3_finalize(stmt);
}

void mx_delete_room_by_id(sqlite3 *db, guint64 id) {
    gchar *request = NULL;
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gint32 rv = SQLITE_OK;

    sqlite3_str_appendf(sqlite_str, "delete from rooms where id = %lu; delete "
                                    "from messages where room_id = %lu;",
                        id, id);
    request = sqlite3_str_finish(sqlite_str);
    rv = sqlite3_exec(db, request, 0, 0, 0);
    mx_error_sqlite(rv, "exec", "delete room");
    sqlite3_free(request);
}

void mx_delete_user_by_id(sqlite3 *db, guint64 id) {
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gint32 rv = SQLITE_OK;
    gchar *request = NULL;

    sqlite3_str_appendf(sqlite_str, "delete from users where id = %lu; delete "
                                    "from contacts where user_id = %lu and whe"
                                    "re user_contact_id = %lu;", id, id, id);
    request = sqlite3_str_finish(sqlite_str);
    rv = sqlite3_exec(db, request, 0, 0, 0);
    mx_error_sqlite(rv, "exec", "delete user");
    sqlite3_free(request);
}



// to delete
void mx_delete_room(sqlite3 *database, char *name_room) {
    sqlite3_str *str = sqlite3_str_new(database);
    char *request = NULL;
    int rv = 0;

    sqlite3_str_appendall(str, "DELETE FROM ROOMS WHERE NAME = '");
    sqlite3_str_appendall(str, name_room);
    sqlite3_str_appendall(str, "'; DROP TABLE '");
    sqlite3_str_appendall(str, name_room);
    sqlite3_str_appendall(str, "'");
    request = sqlite3_str_finish(str);
    rv = sqlite3_exec(database, request, 0, 0, 0);
    if (rv == SQLITE_ERROR)
        mx_logger(MX_LOG_FILE, LOGWAR, "delete room\n");
    sqlite3_free(request);
}

void mx_delete_user(sqlite3 *database, char *login) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(database, "delete from users where login = ?1",
                            -1, 0, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    mx_error_sqlite(rv, "prepare", "delete user");
    mx_error_sqlite(sqlite3_step(stmt), "step", "delete user");
    sqlite3_finalize(stmt);
}

void mx_delete_message(sqlite3 *database, unsigned long long int id,
                       unsigned long long int id_message) {
    char *request = NULL;
    sqlite3_stmt *stmt;
    sqlite3_str *str = sqlite3_str_new(database);
    int rv = SQLITE_OK;

    sqlite3_str_appendall(str, "delete from ");
    sqlite3_str_appendf(str, "room%d", id);
    sqlite3_str_appendall(str, " where id_message = ?1");
    request = sqlite3_str_finish(str);
    rv = sqlite3_prepare_v3(database, request, -1, 0, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id_message);
    mx_error_sqlite(rv, "prepare", "delete message");
    mx_error_sqlite(sqlite3_step(stmt), "step", "delete message");
    sqlite3_free(request);
    sqlite3_finalize(stmt);
}
