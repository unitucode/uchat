#include "server.h"

/*
 * Function: mx_db_push_queue_by_id
 * -------------------------------
 * creates a new record with this query in the database 
 * in the queue table for this user
 * 
 * user_id: user id
 * request: request
 */
void mx_db_push_queue_by_id(sqlite3 *db, guint64 user_id,
                            gchar *request) {
    sqlite3_stmt *stmt;
    gint rv = SQLITE_OK;

    rv = sqlite3_prepare_v2(db, "insert into queue(user_id, request, "
                                "date)values(?1, ?2, ?3);", -1, &stmt, NULL);
    mx_error_sqlite(rv, "db push queue by id");
    sqlite3_bind_int64(stmt, 1, user_id);
    sqlite3_bind_text(stmt, 2, request, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 3, mx_get_time(DB_MILISECOND));
    mx_error_sqlite(sqlite3_step(stmt), "db push queue by id");
    sqlite3_finalize(stmt);
}

/*
 * Function: mx_db_pop_queue_by_id
 * -------------------------------
 * deletes the first recorded query from the database
 * 
 * user_id: user id
 */
void mx_db_pop_queue_by_id(sqlite3 *db, guint64 user_id) {
    sqlite3_str *str = sqlite3_str_new(db);
    gchar *request = NULL;

    sqlite3_str_appendf(str, "delete from queue where user_id = %llu limit 1",
                        user_id);
    request = sqlite3_str_finish(str);
    mx_error_sqlite(sqlite3_exec(db, request, 0, 0, NULL), "db pop queue");
    sqlite3_free(request);
}

/*
 * Function: mx_get_queue
 * -------------------------------
 * receives the first recorded query 
 * in the database and returns it in gchar format
 * 
 * user_id: user id
 * 
 * return: first request of this user
 */

gchar *mx_get_queue(sqlite3 *db, guint64 user_id) {
    sqlite3_stmt *stmt;
    sqlite3_str *str = sqlite3_str_new(db);
    gchar *request = NULL; 
    gchar *sql = NULL;

    sqlite3_str_appendf(str, "select request from queue where user_id = %llu", 
                        user_id);
    sql = sqlite3_str_finish(str);
    mx_error_sqlite(sqlite3_prepare_v2(db, sql, -1, &stmt, NULL), "get queue");
    mx_error_sqlite(sqlite3_step(stmt), "get queue");
    if (sqlite3_column_text(stmt, 0))
        request = strdup((char*)sqlite3_column_text(stmt, 0));
    sqlite3_free(sql);
    sqlite3_finalize(stmt);
    return request;
}

/*
 * Function: mx_clean_queue
 * -------------------------------
 * clean queue of this user
 * 
 * user_id: user id
 */

void mx_clean_queue(sqlite3 *db, guint64 user_id) {
    sqlite3_str *str = sqlite3_str_new(db);
    gchar *sql = NULL;

    sqlite3_str_appendf(str, "delete from queue where user_id = %llu",
                        user_id);
    sql = sqlite3_str_finish(str);
    sqlite3_exec(db, sql, 0, 0, 0);
    sqlite3_free(sql);
}
