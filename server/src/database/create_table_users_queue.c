#include "server.h"

void mx_create_table_queue(sqlite3 *db, char *login) {
    char *request = NULL;
    sqlite3_str *str = sqlite3_str_new(db);
    sqlite3_str *str2 = sqlite3_str_new(db);

    sqlite3_str_appendf(str, "drop table '%s'; create table %s(id integer pr"
                             "imary key not null, request text not null)",
                        login, login);
    sqlite3_str_appendf(str2, "create table '%s'(id integer primary "
                              "key not null, request text not null);", login);
    request = sqlite3_str_finish(str);
    sqlite3_exec(db, request, 0, 0, 0);
    sqlite3_free(request);
    request = sqlite3_str_finish(str2);
    sqlite3_exec(db, request, 0, 0, 0);
    sqlite3_free(request);
}

void mx_delete_queue(sqlite3 *db, char *login) {
    sqlite3_str *str = sqlite3_str_new(db);
    char *request = NULL;

    sqlite3_str_appendf(str, "drop table '%s'", login);
    request = sqlite3_str_finish(str);
    sqlite3_exec(db, request, 0, 0, 0);
    sqlite3_free(request);
}

void mx_insert_into_queue(sqlite3 *db, char *login, char *request) {
    sqlite3_str *str = sqlite3_str_new(db);
    sqlite3_stmt *stmt;
    char *sql = NULL;
    int rv = SQLITE_OK;

    sqlite3_str_appendf(str, "insert into '%s'(request)values(?1);", login);
    sql = sqlite3_str_finish(str);
    rv = sqlite3_prepare_v2(db, request, -1, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "insert into queue");
    sqlite3_bind_text(stmt, 1, request, -1, SQLITE_STATIC);
    mx_error_sqlite(sqlite3_step(stmt), "step", "insert into queue");
    sqlite3_free(sql);
}

// char *mx_get_queue(sqlite3 *db, char *login) {
//     sqlite3_stmt *stmt;
//     sqlite3_str *str = sqlite3_str_new(db);
//     char *request = NULL; 
// }


