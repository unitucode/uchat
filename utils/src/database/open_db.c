#include "utils.h"

sqlite3 *mx_server_data_open(char *name_db) {
    sqlite3 *database;
    int rv;

    if ((rv = sqlite3_open(name_db, &database)) != SQLITE_OK) {
        mx_elogger(MX_LOG_FILE, LOGERR, "error open database");
    }
    mx_create_table_rooms(database);
    mx_create_table_users(database);
    mx_create_table_member(database);
    return database;
}
