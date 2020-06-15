#include "server.h"

sqlite3 *mx_server_data_open(char *name_db) {
    sqlite3 *database;
    int rv;

    if ((rv = sqlite3_open(name_db, &database)) != SQLITE_OK) {
        mx_elogger(MX_LOG_FILE, LOGERR, "error open database");
    }
    mx_create_table_rooms(database);
    mx_create_table_users(database);
    return database;
}

sqlite3 *mx_open_db_json(char *name_db) {
    sqlite3 *db;
    int rv;

    if ((rv = sqlite3_open(name_db, &db)) != SQLITE_OK)
        mx_elogger(MX_LOG_FILE, LOGERR, "error open database");
    mx_create_table_rooms_json(db);
    mx_create_table_users_json(db);
    return db;
}
