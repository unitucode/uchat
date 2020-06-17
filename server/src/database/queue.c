#include "server.h"

void mx_db_push_queue_by_id(sqlite3 *db, guint64 user_id,
                            gchar *request) {
    sqlite3_stmt *stmt;
    gint rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "insert into queue(user_id, request, "
                                "date)values(?1, ?2, ?3);", -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "insert into queue");
    sqlite3_bind_int64(stmt, 1, user_id);
    sqlite3_bind_text(stmt, 2, request, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 3, mx_get_time());
    mx_error_sqlite(sqlite3_step(stmt), "step", "insert into queue");
    sqlite3_finalize(stmt);
}

void mx_db_pop_queue_by_id(sqlite3 *db, guint64 user_id) {
    sqlite3_str *str = sqlite3_str_new(db);
    gchar *request = NULL;

    sqlite3_str_appendf(str, "delete from queue where user_id = %llu limit 1",
                        user_id);
    request = sqlite3_str_finish(str);
    sqlite3_exec(db, request, 0, 0, NULL);
    sqlite3_free(request);
}


// to delete
void mx_db_pop_queue(sqlite3 *db, char *login) {
    sqlite3_str *str = sqlite3_str_new(db);
    char *request = NULL;

    sqlite3_str_appendf(str, "delete from '%s' where id in(select id from '%s' limit 1)", login, login);
    request = sqlite3_str_finish(str);
    sqlite3_exec(db, request, 0, 0, NULL);
    sqlite3_free(request);
}


// to delete
void mx_db_push_queue(sqlite3 *db, char *login, char *request) {
    sqlite3_str *str = sqlite3_str_new(db);
    sqlite3_stmt *stmt;
    char *sql = NULL;
    int rv = SQLITE_OK;

    sqlite3_str_appendf(str, "insert into '%s'(request)values(?1);", login);
    sql = sqlite3_str_finish(str);
    rv = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "insert into queue");
    sqlite3_bind_text(stmt, 1, request, -1, SQLITE_STATIC);
    mx_error_sqlite(sqlite3_step(stmt), "step", "insert into queue");
    sqlite3_finalize(stmt);
    sqlite3_free(sql);
}

char *mx_get_queue(sqlite3 *db, char *login) {
    sqlite3_stmt *stmt;
    sqlite3_str *str = sqlite3_str_new(db);
    char *request = NULL; 
    char *sql = NULL;

    sqlite3_str_appendf(str, "select request from '%s'", login);
    sql = sqlite3_str_finish(str);
    mx_error_sqlite(sqlite3_prepare_v2(db, sql, -1, &stmt, NULL),
                    "prepare", "get_queue");
    mx_error_sqlite(sqlite3_step(stmt), "step", "get_queue");
    if (sqlite3_column_text(stmt, 0))
        request = strdup((char*)sqlite3_column_text(stmt, 0));
    sqlite3_free(sql);
    sqlite3_finalize(stmt);
    return request;
}

void mx_clean_queue(sqlite3 *db, char *login) {
    sqlite3_str *str = sqlite3_str_new(db);
    char *sql = NULL;

    sqlite3_str_appendf(str, "delete from '%s'", login);
    sql = sqlite3_str_finish(str);
    sqlite3_exec(db, sql, 0, 0, 0);
    sqlite3_free(sql);
}

// void mx_clean

