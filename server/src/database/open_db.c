#include "server.h"

sqlite3 *mx_open_db(char *name_db) {
    sqlite3 *database;
    int rv;

    if ((rv = sqlite3_open(name_db, &database)) != SQLITE_OK) {
        mx_elogger(MX_LOG_FILE, LOGERR, "error open database");
    }
    mx_create_table_rooms(database);
    mx_create_table_users(database);
    return database;
}

