#include "server.h"

/*
 * Function: 
 * 
 */

sqlite3 *mx_open_db(gchar *name_db) {
    sqlite3 *db;
    gint32 rv;

    if ((rv = sqlite3_open(name_db, &db)) != SQLITE_OK)
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "error open database");
    mx_create_table(db);
    return db;
}

