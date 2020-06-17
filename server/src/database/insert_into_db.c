#include "server.h"

// to delete 
t_db_room *mx_insert_room_into_db(sqlite3 *database, char *room_name, 
                            char *customer) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(database,
                            "insert into rooms(name, customer, date, desc)"
                            "values(?1, ?2, ?3, ?4);", -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "insert room");
    sqlite3_bind_text(stmt, 1, room_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, customer, -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 3, mx_get_time());
    sqlite3_bind_text(stmt, 4, NULL, -1, SQLITE_STATIC);
    mx_error_sqlite(sqlite3_step(stmt), "step", "insert room");
    sqlite3_finalize(stmt);
    return mx_get_room(database, room_name);
}

//to delete
t_db_user *mx_insert_user_into_db(sqlite3 *db, char *login,
                            char *pass, char *token) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(db,
                            "insert into users(login, password, token, permis"
                            "sion, date, description) values(?1, ?2, ?3, 0, "
                            "strftime('%s', 'now'), '');", -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "insert user");
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pass, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, token, -1, SQLITE_STATIC);
    mx_error_sqlite(sqlite3_step(stmt), "step", "insert user");
    sqlite3_finalize(stmt);
    // mx_create_table_queue(db, login); 
    return mx_get_user_by_login(db, login);
}

void mx_insert_member_into_db(sqlite3 *db, guint64 room_id, guint64 user_id,
                              gint8 permission) {
    gint32 rv = SQLITE_OK;
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gchar *request = NULL;

    sqlite3_str_appendf(sqlite_str, "insert into members(user_id, room_id, date"
                                    ", permission)values(%lu, %lu, %d);",
                        user_id, room_id, permission);
    request = sqlite3_str_finish(sqlite_str);
    rv = sqlite3_exec(db, request, 0, 0, 0);
    mx_error_sqlite(rv, "exec", "insert member");
    sqlite3_free(request);
}
