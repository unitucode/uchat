#include "server.h"

/*
 * cleans structure sqlite3
 * in arguments takes the structure sqlite3
 */

void mx_close_db(sqlite3 *db) {
    gint32 rv = sqlite3_close(db);

    if (rv != SQLITE_OK){
        mx_logger(MX_LOG_FILE, LOGWAR, "close database");
    }
}
