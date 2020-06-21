#include  "server.h"

void mx_insert_contact(sqlite3 *db, guint64 user_id, guint64 contact_id,
                       gint8 type) {
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gchar *request = NULL;

    mx_delete_contact(db, user_id, contact_id);
    sqlite3_str_appendf(sqlite_str, "insert into contacts(user_id, contact_id,"
                                    " type)values(%llu, %llu, %d)", user_id, 
                        contact_id, type);
    request = sqlite3_str_finish(sqlite_str);
    mx_error_sqlite(sqlite3_exec(db, request, 0, 0, 0), "exec", "insert cont");
    sqlite3_free(request);
}

void mx_delete_contact(sqlite3 *db, guint64 user_id, guint64 contact_id) {
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gchar *request = NULL;

    sqlite3_str_appendf(sqlite_str, "delete from contacts where user_id = %llu"
                                    " and contact_id = %llu",
                        user_id, contact_id);
    request = sqlite3_str_finish(sqlite_str);
    mx_error_sqlite(sqlite3_exec(db, request, 0, 0, 0), "exec", "delete cont");
    sqlite3_free(request);
}

// cJSON *mx_get_contact_(sqlite3 *db, guint64 user_id, gint8 type) {
//     sqlite3_stmt *stmt;
//     gint32 rv = SQLITE_OK;


//     rv = sqlite3_prepare_v2(db, "select * from contacts where user_id = ?1 "
//                                 "and type = ?2", -1, &stmt, 0);
//     mx_error_sqlite(rv, "prepare", "get contact of user");
//     sqlite3_bind_int64(stmt, 1, user_id);
//     sqlite3_bind_int(stmt, 2, type);
//     while ((rv = sqlite3_step(stmt) == SQLITE_ROW)) {

//     }
// }

