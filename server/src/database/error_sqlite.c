#include "server.h"

/*
 * Function: mx_error_sqlite
 * -------------------------------
 * takes the returned value and calls the logger if necessary
 * 
 * rv: return value
 */

gboolean mx_error_sqlite(gint32 rv) {
    if (rv != SQLITE_OK && rv != SQLITE_DONE && rv != SQLITE_ROW) {
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "error database");
        return true;
    }
    return false;
}
