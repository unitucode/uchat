#include "server.h"

/*
 * Function: mx_close_db
 * -------------------------------
 * cleans structure sqlite3
 * 
 * db: pointer to the structure sqlite3
 */
void mx_close_db(sqlite3 *db) {
    gint32 rv = sqlite3_close(db);

    if (rv != SQLITE_OK) {
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "close database");
    }
}
