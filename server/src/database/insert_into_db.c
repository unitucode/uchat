#include "server.h"

t_db_message *mx_insert_message_into_db_by_id(sqlite3 *db, char *message_str,
                                        char *login,
                                        unsigned long long int id ){
    sqlite3_stmt *stmt;
    char *request = NULL;
    sqlite3_str *str = sqlite3_str_new(db);
    int rv = 0;

    sqlite3_str_appendall(str, "insert into");
    sqlite3_str_appendf(str, " 'room%llu' ", id);
    sqlite3_str_appendall(str, "(login, date, message) values(?1, strftime"
                               "('%s', 'now'), ?3);");
    request = sqlite3_str_finish(str);
    mx_error_sqlite(sqlite3_prepare_v2(db, request, -1, &stmt, NULL), "prepare", 
                    "insert message into db");
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, message_str, -1, SQLITE_STATIC);
    rv = mx_error_sqlite(sqlite3_step(stmt), "step", "insert message into db");
    sqlite3_finalize(stmt);
    sqlite3_free(request);
    if (rv)
        return NULL;
    return mx_get_last_message(db, id, login);
}

// to delete
t_db_message *mx_insert_message_into_db(sqlite3 *db, char *message_str,
                                     char *login, char *name_room) {
    sqlite3_stmt *stmt;
    char *request = NULL;
    int rv = 0;
    sqlite3_str *str = sqlite3_str_new(db);

    sqlite3_str_appendall(str, "INSERT INTO '" );
    sqlite3_str_appendall(str, name_room);
    sqlite3_str_appendall(str, "' (LOGIN, DATE, MESSAGE) VALUES(?1, strftime"
                               "('%s', 'now'), ?3);");
    request = sqlite3_str_finish(str);
    rv = sqlite3_prepare_v3(db, request, -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "insert message");
    sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, message_str, -1, SQLITE_STATIC);
    mx_error_sqlite(sqlite3_step(stmt), "step", "insert message");
    sqlite3_finalize(stmt);
    sqlite3_free(request);
    return mx_get_last_message(db, mx_get_roomid_by_name(db, name_room), login);
}

t_db_room *mx_insert_room_into_db(sqlite3 *database, char *room_name, 
                            char *customer) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(database,
                            "insert into rooms(name, customer_login, date, desc"
                            "ription) values(?1, ?2, strftime('%s', 'now'), "
                            "'');", -1, 0, &stmt, NULL);
    mx_error_sqlite(rv, "prepare", "insert room");
    sqlite3_bind_text(stmt, 1, room_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, customer, -1, SQLITE_STATIC);
    mx_error_sqlite(sqlite3_step(stmt), "step", "insert room");
    sqlite3_finalize(stmt);
    mx_create_table_room(database, (int)mx_get_roomid_by_name(database, room_name));
    return mx_get_room(database, room_name);
}

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
    mx_create_table_queue(db, login); 
    return mx_get_user_by_login(db, login);
}

void mx_insert_member_into_db(sqlite3 *database, 
                           char *login, char *name_room) {
    sqlite3_stmt *stmt;
    int rv = 0;

    rv = sqlite3_prepare_v3(database,
         "INSERT INTO MEMBER(NAME_ROOM, LOGIN)VALUES(?1, ?2);",
         -1, 0, &stmt, NULL);
    if (rv == SQLITE_ERROR)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_bind_text(stmt, 1, name_room, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, login, -1, SQLITE_STATIC);
    if ((rv = sqlite3_step(stmt)) != SQLITE_DONE)
        mx_elogger(MX_LOG_FILE, LOGERR, "insert database table");
    sqlite3_finalize(stmt);
}
