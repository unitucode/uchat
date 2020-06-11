#include "server.h"

unsigned long long int mx_get_count_messages(sqlite3 *db, 
                                             unsigned long long int id) {
    sqlite3_stmt *stmt;
    sqlite3_str *str = sqlite3_str_new(db);
    char *request = NULL;
    int rv = SQLITE_OK;
    unsigned long long int count = 0;

    sqlite3_str_appendall(str, "select count() from ");
    sqlite3_str_appendf(str, "room%llu", id);
    request = sqlite3_str_finish(str);
    rv = sqlite3_prepare_v2(db, request, -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "get count messages");
    mx_error_sqlite(sqlite3_step(stmt), "step", "get count messages");
    count = sqlite3_column_int(stmt, 0);
    sqlite3_free(request);
    sqlite3_finalize(stmt);
    return count;
}

unsigned long long int mx_get_count_rooms(sqlite3 *db) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;
    unsigned long long int count;

    rv = sqlite3_prepare_v2(db, "select count() from rooms", -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "get count rooms");
    mx_error_sqlite(sqlite3_step(stmt), "step", "get count rooms");
    count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

unsigned long long int mx_get_count_users(sqlite3 *db) {
    sqlite3_stmt *stmt;
    int rv = SQLITE_OK;
    unsigned long long int count;

    rv = sqlite3_prepare_v2(db, "select count() from users", -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "get count users");
    mx_error_sqlite(sqlite3_step(stmt), "step", "get count users");
    count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}
