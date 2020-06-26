#include "server.h"

/*
 * Function: 
 * 
 */

sqlite3 *mx_open_db(gchar *name_db) {
    sqlite3 *db;
    gint32 rv;

    if ((rv = sqlite3_open(name_db, &db)) != SQLITE_OK)
        mx_elogger(MX_LOG_FILE, LOGERR, "error open database");
    mx_create_table(db);
    return db;
}

