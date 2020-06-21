#include "server.h"

sqlite3 *mx_open_db(gchar *name_db) {
    sqlite3 *db;
    gint32 rv;

    if ((rv = sqlite3_open(name_db, &db)) != SQLITE_OK)
        mx_elogger(MX_LOG_FILE, LOGERR, "error open database");
    mx_create_table_rooms(db);
    mx_create_table_users(db);
    mx_create_table_messages(db);
    mx_create_table_member(db);
    mx_create_table_queue(db);
    mx_create_table_contacts(db);
    return db;
}

